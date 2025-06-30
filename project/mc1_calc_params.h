// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file mc1_calc_params.h
 *
 * @brief This file has definitions used in the application to run motor 1,
 *        calculated based on associated user parameter header file
 *        mc1_user_params.h.
 *
 * Component: BOARD
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/


// </editor-fold>

#ifndef __MC1_CALC_PARAMS_H
#define __MC1_CALC_PARAMS_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <stdint.h>
   
#include "mc1_user_params.h"
//#include "general.h"
#include "pwm.h"
#include "adc.h"
#include "clock.h"
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="DEFINITIONS/MACROS ">
#define MC1_LOOPTIME_SEC            (float)(1.0/PWMFREQUENCY_HZ)

#define ADC_CURRENT_SCALE           (float)(MC1_PEAK_CURRENT/32768.0f)
    
#define ADC_VOLTAGE_SCALE           (float)(MC1_PEAK_VOLTAGE/MAX_ADC_COUNT)
  
/* SPEED MULTIPLIER CALCULATION = (((FCY/2)*60)/(TIMER_PRESCALER*POLEPAIRS*6))  */
#define SPEED_MULTIPLIER     (uint32_t)(((float)(FCY/2)/(float)(SPEED_MEASURE_TIMER_PRESCALER*POLE_PAIRS*6))*(float)60)     
        
/* Safe change direction speed interval in seconds*/
#define DIRECTION_CHANGE_SPEED_SEC  (float)  (60/(POLE_PAIRS*6*(DIRECTION_CHANGE_SPEED_RPM + 1)))
/* Safe change direction speed interval in counts */
#define DIRECTION_CHANGE_SPEED_COUNTS ((float)(DIRECTION_CHANGE_SPEED_SEC / MC1_LOOPTIME_SEC))
/* Minimum change direction interval in seconds*/
#define MIN_CHANGE_SPEED_SEC  (float)  (60/(POLE_PAIRS*6*(MINIMUM_SPEED_RPM + 1)))
/* Minimum change direction interval in counts*/
#define MIN_CHANGE_SPEED_COUNTS ((float)(MIN_CHANGE_SPEED_SEC / MC1_LOOPTIME_SEC))
/* Comparator reference for PWM Current Limit PCI from DC Bus current*/ 
#define CMP_REF_DCBUS_FAULT         (uint16_t)(((NOMINAL_CURRENT_BUS_RMS*HALF_ADC_COUNT)/MC1_PEAK_CURRENT)+HALF_ADC_COUNT)
// </editor-fold>

#ifdef __cplusplus
}
#endif

#endif	/* end of __MC1_CALC_PARAMS_H */
