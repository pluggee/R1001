/*
 * imon.h
 *
 *  Created on: May 13, 2017
 *      Author: sherifeid
 */

#ifndef IMON_H_
#define IMON_H_

// Current monitor header

// Current monitor
// Unions
union floatout {
    float f;
    char c[4];
};
extern union floatout idrive;   // measured driver current

#define GT      0.004           // ZXCT1107 transconductance
#define ROUT    2800            // ZXCT1107 output resistor
#define RS      0.05            // current sense resistor

void measIdriver(void);         // measure and process driver current

#endif /* IMON_H_ */
