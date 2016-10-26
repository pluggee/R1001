/*
 * drv8825.c
 *
 *  Created on: Sep 8, 2016
 *      Author: sherifeid
 */

#include "drv8825.h"
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "compiler_defs.h"
#include <intrins.h>
#include "global.h"

// This source includes all control functions for DRV8825 chip

// Global variables
unsigned char IDRVH;
unsigned char IDRVL;
char MCTL;
char MSTAT;
char StepRes;

//-----------------------------------------------------------------------------
// DRV8825 Pin Declarations
//-----------------------------------------------------------------------------
// Output pins
SBIT(DRESETB, SFR_P0, 5);            					// Driver reset pin
SBIT(DSLEEPB, SFR_P0, 6);            					// Driver sleep pin
SBIT(DECAY, SFR_P1, 0);            						// Driver decay pin
SBIT(MODE0, SFR_P1, 1);            						// Driver mode0 pin
SBIT(MODE1, SFR_P1, 2);            						// Driver mode1 pin
SBIT(MODE2, SFR_P1, 3);            						// Driver mode2 pin

// Input pins
SBIT(FAULTB, SFR_P0, 7);
SBIT(HOMEB, SFR_P1, 4);

void SetDecayFast (char val)
{
	// This function sets the decay mode
    // @param val: if true then decay is set fast, otherwise slow
	if (val){
	    DECAY = 1;                                      // set to fast decay
	}
	else{
	    DECAY = 0;                                      // set to slow decay
	}
}

void ResetDriver (void)
{
	unsigned int i; 	    // for loop variable
	// Reset pulse for the motor driver
	DRESETB = 0;			// set resetb to 0, get driver into reset
	for (i=0; i<10000; i++)
	{
		_nop_ ();			// assembly NOP
	}
	DRESETB = 1;			// set resetb to 1, get driver out of reset
//	DSLEEPB = 1;			// get driver out of sleep mode
}

void SetSteppingMode (void)
{
	// this function assigns stepping modes
	// steps	: stepping resolution in power of 2, stepping = 2^steps
	// example, if steps = 4, stepping to 1/16
	// if the input value of 'steps' in invalid (no 1,2,4,8,16,32) then it defaults to 1/32
	switch(StepRes) {
	case 0:
		MODE0 = 0;
		MODE1 = 0;
		MODE2 = 0;
		break;
	case 1:
		MODE0 = 1;
		MODE1 = 0;
		MODE2 = 0;
		break;
	case 2:
		MODE0 = 0;
		MODE1 = 1;
		MODE2 = 0;
		break;
	case 3:
		MODE0 = 1;
		MODE1 = 1;
		MODE2 = 0;
		break;
	case 4:
		MODE0 = 0;
		MODE1 = 0;
		MODE2 = 1;
		break;
	default :
		// defaults to 1/32
		MODE0 = 1;
		MODE1 = 0;
		MODE2 = 1;
	}
}

void SetDriveCurrent (void)
{
    // This function sets the drive current based on that values in IL and IH
    unsigned long drivecurrent;
    drivecurrent = (unsigned long)IDRVH * 256 + (unsigned long)IDRVL;
    if (drivecurrent > 2000){
        // limit drive current to 2A (2000mA)
        drivecurrent = 2000;
        IDRVH = 0x07;               // also update internal IDRVH register
        IDRVL = 0xD0;               // also update internal IDRVL register
    }
    // current = 2A when vout = 2.5V
    // VDD = 3.3V, so max pwm value is 194

//    PCA0CPH0 = (char)((198*drivecurrent) >> 11);                   // set PWMVREF value, ideal 3.3V calculated value
    PCA0CPH0 = (char)((202*drivecurrent) >> 11);                   // set PWMVREF value, compensated after measurement
}

void RefreshMCTL (void)
{
    // This function read the value of MCTL, executes the value and refreshes it
    // first we check for a reset condition
    if ((MCTL & 0x80) != 0){
        // reset condition initiates here
        ResetDriver();
        // set reset flag to zero in MCTL
        MCTL &= 0x7F;
    }

    // set sleep pin
    if ((MCTL & 0x04) == 0){
        // set sleep# pin to 1
        DSLEEPB = 1;
    }
    else{
        // set sleep# pin to 0
        DSLEEPB = 0;
    }

    // look at decay pins
    if ((MCTL & 0x02) == 1){
        // mixed decay bit is set
        // set decay pin P1.0 to open-drain, keep other values to reset state
        P1MDOUT = P1MDOUT_B0__OPEN_DRAIN | P1MDOUT_B1__PUSH_PULL
                | P1MDOUT_B2__PUSH_PULL | P1MDOUT_B3__PUSH_PULL
                | P1MDOUT_B4__OPEN_DRAIN | P1MDOUT_B5__OPEN_DRAIN
                | P1MDOUT_B6__OPEN_DRAIN;

        // set P1.0 pin to high, make sure it's not driving low
        DECAY = 0;
    }
    else{

        // P1.0 to push-pull, keep other values to reset state
        P1MDOUT = P1MDOUT_B0__PUSH_PULL | P1MDOUT_B1__PUSH_PULL
                | P1MDOUT_B2__PUSH_PULL | P1MDOUT_B3__PUSH_PULL
                | P1MDOUT_B4__OPEN_DRAIN | P1MDOUT_B5__OPEN_DRAIN
                | P1MDOUT_B6__OPEN_DRAIN;

        if ((MCTL & 0x01 == 1)){
            // set decay to fast
            SetDecayFast(1);
        }
        else{
            // set decay to slow
            SetDecayFast(0);
        }
    }

    // mask MCTL and set bits 6:3 to 0
    MCTL &= 87;

}

void RefreshMSTAT (void)
{
    // this function refreshes MSTAT register
    MSTAT = 0;                                          // initial value of 0x00

    if (FAULTB == 0){
        MSTAT |= 0x01;                                  // set fault bit
    }

    if (HOMEB == 0){
        MSTAT |= 0x02;                                  // set home bit
    }
}

void drv8825_init(void)
{
    // this function loads the default values and initializes the driver

    // initialize MCTL
    MCTL = 0x81;                    // default value, reset driver and fast decay
    RefreshMCTL();

    // set stepping resolution
    StepRes = StepRes_default;
    SetSteppingMode();

    // initialize drive current
    IDRVH = IDRVH_default;
    IDRVL = IDRVL_default;
    SetDriveCurrent();
}
