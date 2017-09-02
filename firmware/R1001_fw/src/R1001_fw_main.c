
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include "compiler_defs.h"
#include "drv8825.h"
#include "i2c.h"
#include "global.h"
#include "InfoBlock.h"
#include "delay.h"
#include "imon.h"

// $[Generated Includes]
// [Generated Includes]$

// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
uint8_t SMB_DATA_IN[NUM_BYTES_WR];

// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
uint8_t SMB_DATA_OUT[NUM_BYTES_RD];

// Global flags
bit flag_setstep;               // trigger SetSteppingMode()
bit flag_setcurr;               // trigger SetDriveCurrent()
bit flag_refmctl;               // trigger RefreshMCTL()

bit DATA_READY = 0;             // Set to '1' by the SMBus ISR
                                // when a new data byte has been
                                // received.


unsigned short vdd_val;         // value of VDD from 12-bit ADC measurement @ 2.4V (0.5X)

// internal temperature sensor variables

char temp_val;                  // this is where we store the temperature

char i;                         // for loop variable

// Driver Initialization function
void Init (void)
{
//    Timer2Count = 0;                    // initialize timer2 count
//    P2MDOUT = P2MDOUT_B0__PUSH_PULL;    // set C2D/P2.0 as a push-pull output
    drv8825_init();                         // Initialize driver
	SetI2CSlaveAddress();                   // Initialize I2C slave address
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();
	Init();				                // Initialize system

	while (1) 
   {
	    RefreshMSTAT();                             // always refresh

	    if (flag_refmctl){                          // check and execute RefreshMCTL()
	        flag_refmctl = 0;                       // clear flag
	        RefreshMCTL();
	    }

	    if (flag_setcurr){
	        flag_setcurr = 0;                       // clear flag
            SetDriveCurrent();                      // apply new stepping driver current
	    }

	    if (flag_setstep){
	        flag_setstep = 0;                       // clear flag
	        SetSteppingMode();                      // apply new stepping resolution setting
	    }

        // perform temperature and driver current measurement here
	    measTemp();
        measIdriver();

   }
}

void measTemp(void){
    uint32_t ADC_SUM;               // Accumulates the ADC samples

    // measure temperature
    // set analog input to temperature sensor

    // Set voltage reference to 1.65V internal reference
    REF0CN = REF0CN_TEMPE__TEMP_ENABLED | REF0CN_GNDSL__GND_PIN
                | REF0CN_IREFLVL__1P65 | REF0CN_REFSL__INTERNAL_VREF;

    // Select ADC settings with gain = 1X
    ADC0CF = (0x03 << ADC0CF_ADSC__SHIFT) | ADC0CF_AD8BE__NORMAL
                | ADC0CF_ADGN__GAIN_1 | ADC0CF_ADTM__TRACK_NORMAL;

    // Select TEMPERATURE INPUT
    ADC0MX = ADC0MX_ADC0MX__TEMP;

    Delay_ms(5);                                // delay to settle reference and mux switch

    ADC_SUM = 0;                                // reset accumulator
    for (i=0; i<SAMPLING_NUMBER; i++){
        ADC0CN0_ADBUSY = 1;                     // start ADC conversion
        while (!ADC0CN0_ADINT);                 // wait until conversion is complete
        ADC0CN0_ADINT = 0;                      // clear ADC interrupt flag
        ADC_SUM += ADC0 & 0x0fff;               // accumulate value
    }

    temp_val = (char) ((ADC_SUM - TOFFSET)/TSLOPE);    // calculate and store temperature in register
}
