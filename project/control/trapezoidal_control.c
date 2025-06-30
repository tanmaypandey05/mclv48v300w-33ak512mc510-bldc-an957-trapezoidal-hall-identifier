// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file trapezoidal_control.c
 *
 * @brief This module implements control state machine.
 *
 * Component: CONTROL ALGORITHIM
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
#include "board_service.h"
#include "trapezoidal_control.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Global Variables  ">
/* Pointers to PWM states for inverter switching arrays */
uint32_t *PWM1_STATE;
uint32_t *PWM2_STATE;
uint32_t *PWM3_STATE;

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="STATIC FUNCTIONS ">
static void MCAPP_GetControlInputs(MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *);
static void MCAPP_PWM_Override (uint16_t );

// </editor-fold>

/**
* <B> Function: MCAPP_TrapezoidalControlInit(MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *)  </B>
*
* @brief Function to set variables for Control.
*        
* @param 
* @return none.
 * 
* @example
* <CODE> MCAPP_TrapezoidalControlInit(&pTrapezoidalControl); </CODE>
*
*/
void MCAPP_TrapezoidalControlInit(MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *pTrapezoidalControl)
{
    pTrapezoidalControl->piCurrent.inMeasure   = 0;
    pTrapezoidalControl->piCurrent.inReference = 0;
    pTrapezoidalControl->piCurrent.output        = 0;
    pTrapezoidalControl->piSpeed.inMeasure     = 0;
    pTrapezoidalControl->piSpeed.inReference   = 0;
    pTrapezoidalControl->piSpeed.output          = 0;
    MC_ControllerPIReset(&pTrapezoidalControl->piCurrent,0);
    MC_ControllerPIReset(&pTrapezoidalControl->piSpeed,0);
    
    pTrapezoidalControl->avgCurrent                 = 0;
    pTrapezoidalControl->commutationSector          = 0;
    pTrapezoidalControl->controlState               = 0;
    pTrapezoidalControl->directionCmd               = 0;
    pTrapezoidalControl->faultStatus                = 0;
    pTrapezoidalControl->measuredSpeed              = 0;
    pTrapezoidalControl->pwmDuty                    = 0;
    pTrapezoidalControl->sector                     = 0;

    pTrapezoidalControl->ctrlParam.targetCurrent    = 0;
    pTrapezoidalControl->ctrlParam.targetDuty       = 0;
    pTrapezoidalControl->ctrlParam.targetSpeed      = 0;

    pTrapezoidalControl->controlState = CONTROL_LOOP; 
}


/**
* <B> Function: void MCAPP_GetControlInputs (MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *) </B>
*
* @brief Function read motor control inputs.
*
* @param Pointer to the data structure containing Control parameters.
* @return none.
* @example
* <CODE> MCAPP_GetControlInputs(&pControl); </CODE>
*
*/ 
static void MCAPP_GetControlInputs(MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *pControl)
{ 
    MCAPP_MOTOR_T *pMotor = &pControl->motor;
    
    /* Motor current inputs */
    pControl->sector = *(pControl->pSector);
    pControl->measuredSpeed = *(pControl->pMeasuredSpeed);
    pControl->directionCmd  = *(pControl->pDirectionCmd);
    
    if(pControl->directionCmd == 1)
    {
        pControl->commutationSector = 7 - pControl->sector;
    }
    else
    {
        pControl->commutationSector = pControl->sector;
    }
    
    if(pControl->ctrlParam.controlLoop == SPEED_CONTROL)
    {
        /* Speed Input from control input for speed control */
       pControl->ctrlParam.targetSpeed = pMotor->MinSpeed + 
            (((pMotor->MaxSpeed - pMotor->MinSpeed) * 
               pControl->ctrlParam.controlInput)/MAX_ADC_COUNT);
    }
    if(pControl->ctrlParam.controlLoop == CURRENT_CONTROL)
    {
        /* Current Input from control input for current control */
        pControl->ctrlParam.targetCurrent = pMotor->RatedCurrent *
                (pControl->ctrlParam.controlInput/MAX_ADC_COUNT);
        /* Measured filtered bus current */
        pControl->avgCurrent = *(pControl->pAvgCurrent); 
    } 
}

/**
* <B> Function: void MCAPP_TrapezoidalControlStateMachine(MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *)  </B>
*
* @brief Executes Speed, Current and Duty Control Loops and performs actions
*        associated with Trapezoidal control 
*
* @param Pointer to the data structure containing control parameters.
* @return none.
* @example
* <CODE> MCAPP_TrapezoidalControlStateMachine(&pControl); </CODE>
*
*/
void MCAPP_TrapezoidalControlStateMachine(MCAPP_BLDC_TRAPEZOIDAL_CONTROL_T *pControl)
{    
    MCAPP_CONTROL_T *pCtrlParam = &pControl->ctrlParam;
    
    switch (pControl->controlState)
    {
        case CONTROL_INIT:
            MCAPP_TrapezoidalControlInit(pControl); 
            pControl->controlState = CONTROL_LOOP;
            break;
            
        case CONTROL_LOOP:
            
            if( pCtrlParam->controlLoop == CURRENT_CONTROL )
            {
                pControl->controlState = CURRENT_CONTROL_LOOP;
            }
            else if( pCtrlParam->controlLoop == SPEED_CONTROL )
            {
                pControl->controlState = SPEED_CONTROL_LOOP;
            }
            else
                pControl->controlState = CONTROL_OPEN_LOOP;
            break;
        
        case CONTROL_OPEN_LOOP:
            MCAPP_GetControlInputs(pControl);
            MCAPP_PWM_Override(pControl->commutationSector);
            pControl->ctrlParam.targetDuty = 
                    ((float)(pControl->ctrlParam.controlInput *         
                                pControl->pwmPeriod)/MAX_ADC_COUNT);
                    
            pControl->pwmDuty = (uint32_t) pControl->ctrlParam.targetDuty;
            
            break;  
          
        case SPEED_CONTROL_LOOP:
            if(pControl->controlLoopRateCounter > pControl->controlLoopRate)
            {
                MCAPP_GetControlInputs(pControl);
                MCAPP_PWM_Override(pControl->commutationSector);
                /* PI control in Speed Loop */
                pControl->piSpeed.inReference = pControl->ctrlParam.targetSpeed;
                pControl->piSpeed.inMeasure   = pControl->measuredSpeed;
                MC_ControllerPIUpdate(&pControl->piSpeed);
                pControl->pwmDuty = (uint32_t) ((float)(pControl->piSpeed.output * 
                                                            pControl->pwmPeriod)); 
                pControl->controlLoopRateCounter = 0;
            }
            else
            {
                pControl->controlLoopRateCounter++;
            }
            break;
            
        case CURRENT_CONTROL_LOOP:
            MCAPP_GetControlInputs(pControl);
            MCAPP_PWM_Override(pControl->commutationSector);
            
            /* PI control in Current Loop */
            pControl->piCurrent.inReference = pControl->ctrlParam.targetCurrent;
            pControl->piCurrent.inMeasure   = pControl->avgCurrent;
            MC_ControllerPIUpdate(&pControl->piCurrent);
            pControl->pwmDuty = (uint32_t) ((float)(pControl->piCurrent.output * 
                                                        pControl->pwmPeriod)); 
            
            break;

        case CONTROL_FAULT:
                    
            break;
        
        default:
            pControl->controlState = CONTROL_FAULT;
            break;

    } /* End Of switch - case */
}

 /**
* <B> Function: void MCAPP_PWM_Override (uint16_t )  </B>
*
* @brief Function to override PWM outputs.
*
* @param Commutation sector.
* @return none.
* @example
* <CODE> MCAPP_PWM_Override(sector); </CODE>
*
*/
static void MCAPP_PWM_Override(uint16_t sector)
{
   PWM3_OverrideEnableDataSet(PWM3_STATE[sector]); 
   PWM2_OverrideEnableDataSet(PWM2_STATE[sector]); 
   PWM1_OverrideEnableDataSet(PWM1_STATE[sector]); 
}

/**
* <B> Function: void MCAPP_LoadInverterSwitchingArray (uint16_t * , uint16_t *, uint16_t *)  </B>
*
* @brief Function to load switching arrays for BLDC inverter control.
*
* @param switching arrays for PWM1,PWM2, and PWM3.
* @return none.
* @example
* <CODE> MCAPP_LoadInverterSwitchingArray(sector); </CODE>
*
*/
void MCAPP_LoadInverterSwitchingArray(uint32_t *value3, uint32_t *value2, uint32_t *value1)
{
    PWM3_STATE = value3;
    PWM2_STATE = value2;
    PWM1_STATE = value1;
}