/*
 * delay.h
 *
 *  Created on: May 13, 2017
 *      Author: sherifeid
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "compiler_defs.h"

#define SYSCLK 24500000             // 24.5MHz system clock freq

void Delay_us (U8);
void Delay_ms (unsigned int);

#endif /* DELAY_H_ */
