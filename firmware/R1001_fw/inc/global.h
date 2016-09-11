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


//-----------------------------------------------------------------------------
// Global VARIABLES
//-----------------------------------------------------------------------------
extern uint32_t ADC_SUM;               // Accumulates the ADC samples
extern char temp_val;				   // processed temperature value
extern char ADCH;
extern char ADCL;
extern char TSUM[4];					// bytes of ADC SUM
extern char TADCH, TADCL;				// bytes for single ADC read



#endif /* GLOBAL_H_ */
