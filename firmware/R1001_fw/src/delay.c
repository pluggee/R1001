/*
 * delay.c
 *
 *  Created on: May 13, 2017
 *      Author: sherifeid
 */

#include "delay.h"
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations

//-----------------------------------------------------------------------------
// Delay_us
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : 1. time_us - time delay in microseconds
//                   range: 1 to 255
//
// Creates a delay for the specified time (in microseconds) using TIMER2. The
// time tolerance is approximately +/-50 ns (1/SYSCLK + function call time).
//
//-----------------------------------------------------------------------------
void Delay_us (U8 time_us)
{
   TMR2CN0_TR2 = 0;                     // Stop timer
   TMR2CN0_TF2H = 0;                    // Clear timer overflow flag
   TMR2 = -( (U16)(SYSCLK/1000000) * (U16)(time_us) );
   TMR2CN0_TR2 = 1;                     // Start timer
   while(!TMR2CN0_TF2H);                // Wait till timer overflow occurs
   TMR2CN0_TR2 = 0;                     // Stop timer
}

//-----------------------------------------------------------------------------
// Delay_ms
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : 1. time_ms - time delay in milliseconds
//                   range: 1 to 255
//
// Creates a delay for the specified time (in milliseconds) using TIMER2. The
// time tolerance is approximately +/-50 ns (1/SYSCLK + function call time).
//
//-----------------------------------------------------------------------------
void Delay_ms (unsigned int time_ms)
{
   U8 i;

   while(time_ms--)
   {
      for(i = 0; i< 10; i++)           // 10 * 100 microsecond delay
      {
         Delay_us (100);
      }
   }
}
