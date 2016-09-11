
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include "compiler_defs.h"
#include "drv8825.h"
#include "i2c.h"
#include "global.h"

// $[Generated Includes]
// [Generated Includes]$

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
//uint32_t ADC_SUM;               // Accumulates the ADC samples
//bit CONV_COMPLETE;              // ADC accumulated result ready flag




// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
uint8_t SMB_DATA_IN[NUM_BYTES_WR];

// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
uint8_t SMB_DATA_OUT[NUM_BYTES_RD];

bit DATA_READY = 0;                    // Set to '1' by the SMBus ISR
                                       // when a new data byte has been
                                       // received.

// Driver Initialization function
void DriverInit (void)
{
	ResetDriver();
	SetDecayFast();
	SetSteppingMode(5);			// set stepping mode to 1/32
}


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	DriverInit();				// initialize 8825 driver
	SetI2CSlaveAddress();		// Initialize I2C slave address

	while (1) 
   {
		while (!DATA_READY);             // New SMBus data received? gets out of the loop with a command transfer is complete
		DATA_READY = 0;

		// now we look at the contents of the data in the buffer and act accordingly
		switch(SMB_DATA_IN[0]){
		case 0x42:
			// Return the module ID
			// Prepare buffer with ID string
			SMB_DATA_OUT[0] = 1;		// This is for 1000 in R1001
			SMB_DATA_OUT[1] = 1;		// This is for 1 in R1001
			SMB_DATA_OUT[2] = 0x2C;		// just a filler
			break;
		case 0x50:
			// Set stepper motor stepping resolution
			// This is a command to change stepping resolution, set it to the value stored in SMB_DATA_IN[1]
			SetSteppingMode(SMB_DATA_IN[1]);
			break;
		case 0x20:
			// This reads out the temperature value
			SMB_DATA_OUT[0] = temp_val;
			break;
		case 0x21:
			// This reads out the current ADC value
			SMB_DATA_OUT[0] = TADCL;
			SMB_DATA_OUT[1] = TADCH;
			break;
		case 0x22:
			// this reads out the ADC sum bytes
			SMB_DATA_OUT[0] = TSUM[0];
			SMB_DATA_OUT[1] = TSUM[1];
			SMB_DATA_OUT[2] = TSUM[2];
			SMB_DATA_OUT[3] = TSUM[3];
			break;
		default:
			break;
		}
   }                             
}
