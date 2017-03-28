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
extern uint32_t ADC_SUM;                // Accumulates the ADC samples
extern char temp_val;				    // processed temperature value
extern char ADCH;                       // ADC higher byte
extern char ADCL;                       // ADC lower byte
extern char TSUM[4];					// bytes of ADC SUM
extern char TADCH, TADCL;				// bytes for single ADC read
extern char StepRes;                    // stepper motor resolution, power of 2 (i.e 4 -> 2^4 steps, 16)
extern char writelen;                   // this is a global variable to store the length of I2C write command
                                        // if it is 1, that means the intention is to read the register
                                        // if it is more, then the intention is to write the value to the register
extern unsigned char IDRVH;             // high byte for driver current
extern unsigned char IDRVL;             // low byte for driver current
                                        // Driver current = IDRVH:IDRVL in milliamps
extern char MCTL;                       // motor control register
extern char MSTAT;                      // motor status register


// I2C REGISTER/COMMAND Definitions
// ---------------------------------
#define TGT_CMD_RESET_MCU           0x00
#define TGT_CMD_PLID                0x01
#define TGT_CMD_DVID                0x02
#define TGT_CMD_FWID                0x03

#define TGT_CMD_TMP                 0x10    // read temperature register

#define TGT_CMD_BLSTAT              0x0B    // bootloader/application status, returs 0x03 if in bootloader, 0x00 if in application


#define TGT_CMD_STP                 0x20    // stepper motor register
#define TGT_CMD_IDRVL               0x21    // stepper motor current - low byte
#define TGT_CMD_IDRVH               0x22    // stepper motor current - high byte

#define TGT_CMD_MCTL                0x23    // motor control register
#define TGT_CMD_MSTAT               0x24    // motor status register


#define TGT_CMD_ERASE_FLASH_PAGE    0x05
#define TGT_CMD_WRITE_FLASH_BYTES   0x06
#define TGT_CMD_READ_FLASH_BYTES    0x07
#define TGT_CMD_CHECK_SIG           0x08
#define TGT_CMD_CHECK_BLSTAT        0x0B
#define TGT_CMD_START_APPFW         0x0C

#endif /* GLOBAL_H_ */
