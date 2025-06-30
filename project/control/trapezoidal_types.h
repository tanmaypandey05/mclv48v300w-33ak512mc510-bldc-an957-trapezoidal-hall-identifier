// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
* @file trapezoidal_types.h
*
* @brief This module has variable type definitions of data structure
* holding Trapezoidal control parameters and enumerated constants.
*
* Component: Trapezoidal Control
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

#ifndef __TRAPEZOIDAL_TYPES_H
#define	__TRAPEZOIDAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include <stdbool.h>
#include "motor_types.h"
#include "trapezoidal_control_types.h"
#include "pi.h"
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="ENUMERATED CONSTANTS ">

typedef enum
{
    CONTROL_INIT = 0,                   /* Initialize control parameters */
    CONTROL_LOOP = 1,                   /* Select control loop */
    CONTROL_OPEN_LOOP = 2,              /* Open loop duty control */
    SPEED_CONTROL_LOOP = 3,             /* Closed loop Current control */
    CURRENT_CONTROL_LOOP = 4,           /* Closed loop Speed control */
    CONTROL_FAULT = 5,                  /* Control state machine is in Fault */ 
            
}TRAPEZOIDAL_CONTROL_STATE_T;

typedef enum
{
    SPEED_CONTROL       = 1,       
    CURRENT_CONTROL     = 2,       
    OPEN_LOOP           = 3,       
            
}MCAPP_CRTL_LOOP_T;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="VARIABLE TYPE DEFINITIONS ">

typedef struct
{
    uint16_t
        *pSector,           /* Pointer for Hall sector */
        *pDirectionCmd,     /* Pointer for direction command */
        sector,             /* Variable for Hall sector value */
        commutationSector,  /* Variable for sector to commutate */ 
        directionCmd,       /* Variable for direction command */
        faultStatus,        /* Variable for Fault Status */
        controlState,       /* State variable for control state machine */
        controlLoopRateCounter,   /* Index counter for PI control loop */
        controlLoopRate;          /* Variable for rate of execution of control loop */
    uint32_t
        pwmDuty,            /* Variable for PWM duty */
        pwmPeriod;          /* Variable for PWM period */
    float
        *pMeasuredSpeed,    /* Pointer for Speed */
        *pAvgCurrent,       /* Pointer for average current */
        measuredSpeed,      /* Variable for speed */
        avgCurrent;         /* Variable for average current */
    
    
    MCAPP_MOTOR_T  motor;   /* Motor parameters */
    
    /* Parameters for PI Current controllers */ 
    MC_PI_T     piCurrent;
    
    /* Parameters for PI Speed controllers */ 
    MC_PI_T     piSpeed;
    
    MCAPP_CONTROL_T
        ctrlParam;          /* Parameters for control references */
    
}MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T;

// </editor-fold>

#ifdef __cplusplus
}
#endif

#endif /* end of __TRAPEZOIDAL_TYPES_H */

