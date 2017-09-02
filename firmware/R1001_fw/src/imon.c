/*
 * imon.c
 *
 *  Created on: May 13, 2017
 *      Author: sherifeid
 */

#include "imon.h"
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "delay.h"

union floatout idrive;                  // declare idrive globally

void measIdriver(void){

    unsigned int voutadc;                   // store output of ADC
    // measure ZXCT1107SA-7 output
    // Set voltage reference to 1.65V internal reference
    REF0CN = REF0CN_TEMPE__TEMP_ENABLED | REF0CN_GNDSL__GND_PIN
                | REF0CN_IREFLVL__1P65 | REF0CN_REFSL__INTERNAL_VREF;

    // Select ADC settings with gain = 1X
    ADC0CF = (0x03 << ADC0CF_ADSC__SHIFT) | ADC0CF_AD8BE__NORMAL
                | ADC0CF_ADGN__GAIN_1 | ADC0CF_ADTM__TRACK_NORMAL;

    // Select 0.6 port input, where ZXCT1107 it connected
    ADC0MX = ADC0MX_ADC0MX__ADC0P6;

    Delay_ms(5);                            // delay to settle reference and mux switch



    ADC0CN0_ADBUSY = 1;                     // start ADC conversion
    while (!ADC0CN0_ADINT);                 // wait until conversion is complete
    ADC0CN0_ADINT = 0;                      // clear ADC interrupt flag
    voutadc = (unsigned int)ADC0;           // accumulate value

    // calculate driver current and place value in global variable
    idrive.f = (voutadc * 1.65/(4096*GT*RS*ROUT));      // evaluate driver current
}
