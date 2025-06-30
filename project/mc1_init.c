// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file mc1_init.c
 *
 * @brief This module initializes data structure holding motor control
 * parameters required to run motor 1 using field oriented control.
 * In this application to initialize variable required to run the application.
 *
 * Component: APPLICATION (Motor Control 1 - mc1)
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

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "mc1_init.h"
#include "board_service.h"
#include "mc1_user_params.h"
#include "mc1_calc_params.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="STATIC FUNCTIONS ">

static void MCAPP_MC1ControlSchemeConfig(MC1APP_DATA_T *);

// </editor-fold>

/**
* <B> Function: MCAPP_MC1ParamsInit (MC1APP_DATA_T *)  </B>
*
* @brief Function to reset variables used for current offset measurement.
*
* @param Pointer to the Application data structure required for 
* controlling motor 1.
* @return none.
* 
* @example
* <CODE> MCAPP_MC1ParamsInit(&pMCData); </CODE>
*
*/
void MCAPP_MC1ParamsInit(MC1APP_DATA_T *pMCData)
{    
    /* Reset all variables in the data structure to '0' */
    memset(pMCData,0,sizeof(MC1APP_DATA_T));

    pMCData->pControlScheme = &pMCData->controlScheme;
    pMCData->pMotorInputs = &pMCData->motorInputs;
    
    /* Configure Control Scheme */
    MCAPP_MC1ControlSchemeConfig(pMCData);
    
    /* Set motor control state as 'MTR_INIT' */
    pMCData->appState = MCAPP_INIT;
}

/**
* <B> Function: MCAPP_MC1ControlSchemeConfig (MC1APP_DATA_T *)  </B>
*
* @brief Function to configure the control scheme and parameters
*
* @param Pointer to the Application data structure required for 
* controlling motor 1.
* @return none.
* 
* @example
* <CODE> MCAPP_MC1ControlSchemeConfig(&pMCData); </CODE>
*
*/
void MCAPP_MC1ControlSchemeConfig(MC1APP_DATA_T *pMCData)
{
    MCAPP_CONTROL_SCHEME_T *pControlScheme;
    MCAPP_MEASURE_T *pMotorInputs;

    pControlScheme = pMCData->pControlScheme;
    pMotorInputs = pMCData->pMotorInputs;
 
    /* Configure Inputs */    
    pControlScheme->pDirectionCmd = &pMCData->directionCmd;
    pControlScheme->pMeasuredSpeed = 
                        &pMotorInputs->detectRotorPosition.calculateSpeed.speed;
    pControlScheme->pSector = &pMotorInputs->detectRotorPosition.value;
    pControlScheme->pAvgCurrent = &pMotorInputs->filterBusCurrent;
    
    /* Initialize Motor parameters */
    pControlScheme->motor.MaxSpeed        =  MAXIMUM_SPEED_RPM;
    pControlScheme->motor.MinSpeed        =  MINIMUM_SPEED_RPM;
    pControlScheme->motor.RatedCurrent    =  NOMINAL_CURRENT_BUS_RMS;

    /* Initialize Trapezoidal control parameters */
#if CLOSED_LOOP == 0
    pControlScheme->ctrlParam.controlLoop = OPEN_LOOP;
#elif CLOSED_LOOP == 1
    pControlScheme->ctrlParam.controlLoop = SPEED_CONTROL;
#elif CLOSED_LOOP == 2
    pControlScheme->ctrlParam.controlLoop = CURRENT_CONTROL;
#else 
    pControlScheme->ctrlParam.controlLoop = SPEED_CONTROL;
#endif       
    pControlScheme->controlLoopRate = CRTL_LOOP_RATE;
    /* Initialize startup parameters */
    pMotorInputs->detectRotorPosition.calculateSpeed.multiplier = 
                                                               SPEED_MULTIPLIER;   
    pMotorInputs->detectRotorPosition.motorStopValue = (uint32_t)
                                        DIRECTION_CHANGE_SPEED_COUNTS;
    pMotorInputs->detectRotorPosition.motorStallValue = (uint32_t)
                                        MIN_CHANGE_SPEED_COUNTS;
    
    /* Initialize PI controller used for current control */
    pControlScheme->piCurrent.param.kp        =   CURRCNTR_PTERM;
    pControlScheme->piCurrent.param.ki        =   CURRCNTR_ITERM;
    pControlScheme->piCurrent.param.outMax    =   CURRCNTR_OUTMAX;

    /* Initialize PI controller used for speed control */
    pControlScheme->piSpeed.param.kp          =   SPEEDCNTR_PTERM;
    pControlScheme->piSpeed.param.ki          =   SPEEDCNTR_ITERM;
    pControlScheme->piSpeed.param.outMax      =   SPEEDCNTR_OUTMAX;
    pControlScheme->piSpeed.param.outMin      =   SPEEDCNTR_OUTMIN;
    
    /* Output Initializations */
    pControlScheme->pwmPeriod = LOOPTIME_TCY; 
}