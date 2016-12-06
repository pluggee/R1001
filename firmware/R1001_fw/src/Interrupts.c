//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8BB1_Register_Enums.h>
#include "compiler_defs.h"
#include "i2c.h"
#include "global.h"
#include "math.h"


//extern uint32_t ADC_SUM;               // Accumulates the ADC samples
//extern bit CONV_COMPLETE;              // ADC accumulated result ready flag

uint32_t ADC_SUM;                           // Accumulates the ADC samples
//bit CONV_COMPLETE;                        // ADC accumulated result ready flag
char temp_val;
char TSUM[4];                               // bytes of ADC SUM
char TADCH, TADCL;                          // bytes for single ADC read

char writelen = 0;

// temperature sensor constants
#define DS_SLOPE				0.00285		// slope from datasheet in V/C
#define DS_OFFSET				0.757		// offset from datasheet in V

#define SAMPLING_2N             4			// number of samples (power of 2)
#define SAMPLING_NUMBER         16			// = 2^SAMPLING_2N
#define TSLOPE                	113			// slope LSB's/C = round(SAMPLING_NUMBER*DS_SLOPE/LSBSize)
#define TOFFSET                 30067		// Offset in LSB's = round(SAMPLING_NUMBER*DS_OFFSET/LSBSize)

// pin declarations
//SBIT(PWMREF, SFR_P1, 4);            						// Driver mode2 pin

//-----------------------------------------------------------------------------
// TIMER0_ISR
//-----------------------------------------------------------------------------
//
// TIMER0 ISR Content goes here. Remember to clear flag bits:
// TCON::TF0 (Timer 0 Overflow Flag)
//
//-----------------------------------------------------------------------------
//SI_INTERRUPT (TIMER0_ISR, TIMER0_IRQn)
//{
//}

//-----------------------------------------------------------------------------
// SMBUS0_ISR
//-----------------------------------------------------------------------------
//
// SMBUS0 ISR Content goes here. Remember to clear flag bits:
// SMB0CN0::SI (SMBus Interrupt Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (SMBUS0_ISR, SMBUS0_IRQn)
{
	static uint8_t sent_byte_counter;
	static uint8_t rec_byte_counter;

	if (SMB0CN0_ARBLOST == 0)
	{
		switch (SMB0CN0 & 0xF0)          // Decode the SMBus status vector
		{
			// Slave Receiver: Start+Slave Address received
			case SMB_SRADD:
                SMB0CN0_STA = 0;// Clear SMB0CN0_STA bit

                sent_byte_counter = 1;// Reinitialize the data counters
                rec_byte_counter = 1;

                if ((SMB0DAT & 0x01) == READ)// If the transfer is a master READ,
                {
                    // Prepare outgoing byte
                    SMB0DAT = SMB_DATA_OUT[sent_byte_counter-1];
                    sent_byte_counter++;
                }

                // need to add an acknowledge here????
                // added an ack here
                SMB0CN0_ACK = 1;// send an acknowledge that address and command are received

                break;

			// Slave Receiver: Data received
			case SMB_SRDB:
                if (rec_byte_counter < NUM_BYTES_WR)
                {
                    // Store incoming data
                    SMB_DATA_IN[rec_byte_counter-1] = SMB0DAT;
                    rec_byte_counter++;
                    SMB0CN0_ACK = 1;         // SMB0CN0_ACK received data
                }
                else
                {
                    // Store incoming data
                    SMB_DATA_IN[rec_byte_counter-1] = SMB0DAT;
                    DATA_READY = 1;         // Indicate new data fully received
                }
                writelen++;                 // increment global write length counter
                break;

			// Slave Receiver: Stop received while either a Slave Receiver or
			// Slave Transmitter
			case SMB_SRSTO:
                SMB0CN0_STO = 0;            // SMB0CN0_STO must be cleared by software when
                                            // a STOP is detected as a slave

                DATA_READY = 1;             // Indicates end of transmission
                break;

			// Slave Transmitter: Data byte transmitted
			case SMB_STDB:
                if (SMB0CN0_ACK == 1)// If Master SMB0CN0_ACK's, send the next byte
                {
                    if (sent_byte_counter <= NUM_BYTES_RD)
                    {
                        // Prepare next outgoing byte
                        SMB0DAT = SMB_DATA_OUT[sent_byte_counter-1];
                        sent_byte_counter++;
                    }
                }                          // Otherwise, do nothing
                break;

			// Slave Transmitter: Arbitration lost, Stop detected
			//
			// This state will only be entered on a bus error condition.
			// In normal operation, the slave is no longer sending data or has
			// data pending when a STOP is received from the master, so the SMB0CN0_TXMODE
			// bit is cleared and the slave goes to the SRSTO state.
			case SMB_STSTO:
                SMB0CN0_STO = 0;            // SMB0CN0_STO must be cleared by software when
                                            // a STOP is detected as a slave
                break;

          // Default: all other cases undefined
            default:
                SMB0CF &= ~0x80;// Reset communication
                SMB0CF |= 0x80;
                SMB0CN0_STA = 0;
                SMB0CN0_STO = 0;
                SMB0CN0_ACK = 1;
                break;
		}
	}
	// SMB0CN0_ARBLOST = 1, Abort failed transfer
	else
	{
		SMB0CN0_STA = 0;
		SMB0CN0_STO = 0;
		SMB0CN0_ACK = 1;
	}

	SMB0CN0_SI = 0;                     // Clear SMBus interrupt flag
}

//-----------------------------------------------------------------------------
// ADC0EOC_ISR
//-----------------------------------------------------------------------------
//
// ADC0EOC ISR Content goes here. Remember to clear flag bits:
// ADC0CN0::ADINT (Conversion Complete Interrupt Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (ADC0EOC_ISR, ADC0EOC_IRQn)
{
	   static uint32_t accumulator = 0;         // Accumulator for averaging
	   static uint16_t measurements = SAMPLING_NUMBER; // Measurement counter

	   uint32_t temp_adc;						// ADC reading of temperature

	   ADC0CN0_ADINT = 0;                       // Clear ADC0 conv. complete flag

	   // Checks if obtained the necessary number of samples
	   if(measurements == 0)
	   {
	      ADC_SUM = accumulator;           // Copy total into ADC_SUM
	      measurements = SAMPLING_NUMBER;  // Reset counter
	      accumulator = 0;                 // Reset accumulator

	      // conversion is complete, perform calculation and store it in memory
	      temp_adc = ((ADC_SUM - TOFFSET)/TSLOPE);
	      temp_val = (char) (temp_adc);	   // convert to 8-bit

	      TSUM[0] = ADC_SUM & 0xff;
	      TSUM[1] = (ADC_SUM >> 8) & 0xff;
	      TSUM[2] = (ADC_SUM >> 16) & 0xff;
	      TSUM[3] = (ADC_SUM >> 24) & 0xff;
	   }
	   else
	   {
	      TADCL = ADC0 & 0xff;				   // store higher byte
	      TADCH = (ADC0 >> 8) & 0xff;		   // store lower byte
		  accumulator += ADC0 & 0x0fff;       // get 12 bit value (only)
	      measurements--;
	   }
}

