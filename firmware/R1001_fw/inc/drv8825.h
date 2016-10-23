/*
 * drv8825.h
 *
 *  Created on: Sep 8, 2016
 *      Author: sherifeid
 */

#ifndef DRV8825_H_
#define DRV8825_H_

// function declarations
void drv8825_init(void);

void SetDecayFast (char);
void ResetDriver (void);
void SetSteppingMode (void);
void SetDriveCurrent (void);
void RefreshMCTL (void);
void RefreshMSTAT (void);

#endif /* DRV8825_H_ */
