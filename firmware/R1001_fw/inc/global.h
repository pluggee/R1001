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

#endif /* GLOBAL_H_ */
