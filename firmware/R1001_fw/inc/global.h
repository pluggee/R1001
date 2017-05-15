/*
 * global.h
 *
 *  Created on: Sep 10, 2016
 *      Author: sherifeid
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define StepRes_default         5       // default stepping resolution to 1/32
#define MCTL_default            0x81    // default to reset driver, no sleep and fast decay mode
#define IDRVH_default           0x03    // default drive current to 1000mA
#define IDRVL_default           0xE8

//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
extern char temp_val;				    // processed temperature value
extern char StepRes;                    // stepper motor resolution, power of 2 (i.e 4 -> 2^4 steps, 16)
extern char writelen;                   // this is a global variable to store the length of I2C write command
                                        // if it is 1, that means the intention is to read the register
                                        // if it is more, then the intention is to write the value to the register
extern unsigned char IDRVH;             // high byte for driver current
extern unsigned char IDRVL;             // low byte for driver current
                                        // Driver current = IDRVH:IDRVL in milliamps
extern char MCTL;                       // motor control register
extern char MSTAT;                      // motor status register

extern unsigned short vdd_val;          // value of VDD from 12-bit ADC measurement @ 2.4V (0.5X)

// Global flags
extern bit flag_setstep;                // trigger SetSteppingMode()
extern bit flag_setcurr;                // trigger SetDriveCurrent()
extern bit flag_refmctl;                // trigger RefreshMCTL()


// I2C REGISTER/COMMAND Definitions
// ---------------------------------
#define TGT_CMD_RESET_MCU           0x00
#define TGT_CMD_PLID                0x01
#define TGT_CMD_DVID                0x02
#define TGT_CMD_FWID                0x03

#define TGT_CMD_TMP                 0x10    // read temperature register
#define TGT_CMD_VDD                 0x11    // read internal VDD value

#define TGT_CMD_BLSTAT              0x0B    // bootloader/application status, returs 0x03 if in bootloader, 0x00 if in application

#define TGT_CMD_STP                 0x20    // stepper motor register
#define TGT_CMD_IDRVL               0x21    // stepper motor current - low byte
#define TGT_CMD_IDRVH               0x22    // stepper motor current - high byte

#define TGT_CMD_MCTL                0x23    // motor control register
#define TGT_CMD_MSTAT               0x24    // motor status register

#define TGT_CMD_IDRIVER             0x25    // measure driver current

#define TGT_CMD_ERASE_FLASH_PAGE    0x05
#define TGT_CMD_WRITE_FLASH_BYTES   0x06
#define TGT_CMD_READ_FLASH_BYTES    0x07
#define TGT_CMD_CHECK_SIG           0x08
#define TGT_CMD_CHECK_BLSTAT        0x0B
#define TGT_CMD_START_APPFW         0x0C

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define PLATFORM    0x01        // platform ID, 0x01 for R1000A
#define DEVID       0x01        // device ID, 0x01 for R1001 stepper motor driver

// temperature sensor constants
#define DS_SLOPE                    0.00285     // slope from datasheet in V/C
#define DS_OFFSET                   0.757       // offset from datasheet in V
#define SAMPLING_2N                 4         // number of samples (power of 2)
#define SAMPLING_NUMBER             16            // = 2^SAMPLING_2N
#define TSLOPE                      113         // slope LSB's/C = round(SAMPLING_NUMBER*DS_SLOPE/LSBSize)
#define TOFFSET                     30067     // Offset in LSB's = round(SAMPLING_NUMBER*DS_OFFSET/LSBSize)

void measTemp(void);                // prototype for internal temperature measurement

#endif /* GLOBAL_H_ */
