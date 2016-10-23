
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
//#define PLATFORM    0x01        // platform ID, 0x01 for R1000A
#define PLATFORM    0xae        // platform ID, 0x01 for R1000A
//#define DEVID       0x01        // device ID, 0x01 for R1001 stepper motor driver
#define DEVID       0xc0        // device ID, 0x01 for R1001 stepper motor driver
//#define FWVER       0x01        // firmware release
#define FWVER       0xee        // firmware release
//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------


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
void Init (void)
{
	drv8825_init();                     // Initialize driver
	SetI2CSlaveAddress();               // Initialize I2C slave address
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
		while (!DATA_READY);             // New SMBus data received? gets out of the loop with a command transfer is complete
		DATA_READY = 0;

		// now we look at the contents of the data in the buffer and act accordingly
		switch(SMB_DATA_IN[0]){
		case 0x01:
			// Return the module ID
			// Prepare buffer with ID string
			SMB_DATA_OUT[0] = PLATFORM;     // Platform ID
			break;
		case 0x02:
			// Return the module ID
			// Prepare buffer with ID string
			SMB_DATA_OUT[0] = DEVID;        // device ID
			break;
		case 0x03:
			// Return the module ID
			// Prepare buffer with ID string
			SMB_DATA_OUT[0] = FWVER;        // firmware version
			break;
		case 0x10:
            // This reads out the temperature value
            SMB_DATA_OUT[0] = temp_val;
            break;
		case 0x20:
			// Set stepper motor stepping resolution
			// This is a command to change stepping resolution, set it to the value stored in SMB_DATA_IN[1]
		    if (writelen > 1){
			    StepRes = SMB_DATA_IN[1];       // store new value to internal variable
			    SetSteppingMode();              // apply new stepping resolution setting
			}
		    SMB_DATA_OUT[0] = StepRes;
			break;
		case 0x21:
		    // here we check if writing to IDRVL and IDRVH
		    if (writelen == 2){
                // only write IDRVL
		        IDRVL = SMB_DATA_IN[1];         // store new value to internal variable
		        SetDriveCurrent();              // apply new stepping driver current
            }
		    else if (writelen > 2){
                // write IDRVL & IDRVH
                IDRVL = SMB_DATA_IN[1];         // store new value to internal variable
                IDRVH = SMB_DATA_IN[2];         // store new value to internal variable
                SetDriveCurrent();              // apply new stepping driver current
            }

		    // Store IDRVL/H values into output buffer
		    SMB_DATA_OUT[0] = IDRVL;
			SMB_DATA_OUT[1] = IDRVH;
			break;
		case 0x22:
            // here we check if writing to IDRVH
            if (writelen > 1){
                // only write IDRVH
                IDRVH = SMB_DATA_IN[1];         // store new value to internal variable
                SetDriveCurrent();              // apply new stepping driver current
            }
            // Store IDRVH value in output buffer
            SMB_DATA_OUT[0] = IDRVH;
			break;
		case 0x23:
		    // Stepper driver control register
		    if (writelen > 1){
                // parse input and execute values
                MCTL = SMB_DATA_IN[1];          // store new value to internal variable
                RefreshMCTL();                  // apply new stepping driver current
            }
		    SMB_DATA_OUT[0] = MCTL;             // place refreshed MCTL value in output buffer
		    break;
		case 0x24:
		    // refresh status register before pushing it out
		    RefreshMSTAT();
            SMB_DATA_OUT[0] = MSTAT;             // place refreshed MCTL value in output buffer
            break;
		case 0x25:
		    // FIXME, experimental, remove this
		    SMB_DATA_OUT[0] = PCA0CPH0;
		    break;
		default:
			break;
		}
   }                             
}
