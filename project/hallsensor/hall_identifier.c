// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file hall.c
 *
 * @brief This module can be used for detecting hall pattern
 * 
 * Note : It is assumed that this function  HallSeqIdentifier_Execute() 
   is called at a specific interval and bus current is used as feedback 
   for current control.  
 * Also the change notification interrupt should be disabled when this 
 * identification technique is running.
 * 
 * Component: Hall Sequence Identifier
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
#include <xc.h>
#include "hall_identifier.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="CONSTANTS">

/* 
* Voltage vector vs electrical angle in degrees
* Voltage vector sequence applied to the motor :
*                                   [ 100  ,  110 ,  010 ,  011 , 001 , 101 ]              
* Rotor position electrical (degrees) :        
*                                   [  0   ,  60  ,  120 ,  180 , 240 , 300 ]
* 
*/
/* Three-phase vector (as in Space Vector Modulation) applied to the motor 
                                   to determine the hall sequence pattern */
const uint32_t SVMvector3[6]	=	{DC_MINUS,DC_MINUS,DC_MINUS,DC_PLUS ,DC_PLUS ,DC_PLUS};
const uint32_t SVMvector2[6]	=	{DC_MINUS,DC_PLUS ,DC_PLUS ,DC_PLUS ,DC_MINUS,DC_MINUS};
const uint32_t SVMvector1[6]	=	{DC_PLUS ,DC_PLUS ,DC_MINUS,DC_MINUS,DC_MINUS,DC_PLUS};

/*  Two-phase voltage vector typically applied to the motor 
                                           for trapezoidal control  */
const uint32_t bldcVector3[6]	=	{DC_MINUS,PWM_OFF ,DC_PLUS ,DC_PLUS ,PWM_OFF ,DC_MINUS};
const uint32_t bldcVector2[6]	=	{DC_PLUS ,DC_PLUS ,PWM_OFF ,DC_MINUS,DC_MINUS,PWM_OFF};
const uint32_t bldcVector1[6]	=	{PWM_OFF ,DC_MINUS,DC_MINUS,PWM_OFF ,DC_PLUS ,DC_PLUS};


// </editor-fold>

/**
* <B> Function: HallSeqIdentifier_Init(MCAPP_HALLSEQ_IDENT_T*, int32_t) </B>
*
* @brief Function initializes the parameters of hall sequence identifier
*        .
* @param Pointer to the data structure containing parameters of 
         the hall sequence identifier.
* @param PWM period.
* @return none.
* @example
* <CODE> HallSeqIdentifier_Init(&hallSeqIdentifier, pwmPeriod); </CODE>
*
*/
void HallSeqIdentifier_Init(MCAPP_HALLSEQ_IDENT_T* pData, uint32_t pwmPeriod)
{
    pData->piCurrent.param.kp         = HALLSEQ_CURRENT_KP;
    pData->piCurrent.param.ki         = HALLSEQ_CURRENT_KI;
    pData->piCurrent.param.outMax     = HALLSEQ_CURRENT_OUTMAX;
    pData->piCurrent.param.outMin     = 0;
    pData->piCurrent.stateVar.integrator = 0;
    pData->piCurrent.output           = 0;
    pData->pwmPeriod                  = pwmPeriod;
    /* Status to state algorithm is running*/
    pData->status = 0;
    /* Flag to indicate whether the algorithm is currently running */
    pData->executionFlag = 0;
}

/**
* <B> Function: HallSeqIdentifier_Execute(MCAPP_HALLSEQ_IDENT_T*, float) </B>
*
* @brief Function to execute the hall sequence identifier. 
*        .
* @param Pointer to the data structure containing parameters of 
         the hall sequence identifier. 
* @param Measured bus current feedback.
* @return none.
* @example
* <CODE> HallSeqIdentifier_Execute(&hallSeqIdentifier, Ibus); </CODE>
*
*/
void HallSeqIdentifier_Execute(MCAPP_HALLSEQ_IDENT_T* pData, float Ibus)
{            
    if(pData->vector < HALL_SECTOR)
    {
        /* Current Control based on bus current feedback. For limiting 
         the current to the motor winding during the hall sequence identification*/
        pData->piCurrent.inReference = HALLSEQ_CURRENT_LIMIT_AMPS; 
        pData->piCurrent.inMeasure = Ibus;
        MC_ControllerPIUpdate(&pData->piCurrent);
        
        /* Compute duty cycle */
        pData->dutyCycle = (uint32_t) ((float)(pData->piCurrent.output * 
                                                            pData->pwmPeriod)); 

        /* Load the duty cycle */
        HAL_PWM_DutyCycleRegister_Set(pData->dutyCycle);

        /* Load the voltage vector to corresponding PWM registers of each phase 
           of three phase inverter */      
        PWM3_OverrideEnableDataSet(SVMvector3[pData->vector]);
        PWM2_OverrideEnableDataSet(SVMvector2[pData->vector]);
        PWM1_OverrideEnableDataSet(SVMvector1[pData->vector]); 
        
        /* Increment the interval counter */
        pData->intervalCount++;  
        
        if ( pData->intervalCount > VECTOR_COMMUTATION_INTERVAL) 
        {
            /* Reading the Hall sensor value from the input port */
            pData->hallSector = MCAPP_HallSensorRead(&pData->hallInput);
            /* Present Hall value */
            pData->presentValue = pData->hallSector;
            /* Checking for change in  Hall sector */
            if(pData->presentValue != pData->previousValue)
            {
                pData->previousValue = pData->presentValue;
            }
            else
            {
                /* Failure in hall sequence detection */
                pData->failure = 1;
            }
            /* Loading the hall sensor values into an array for reference */
            pData->sectorSequence[pData->hallSector] = pData->hallSector; 
            
            /* Load the PWM override data based on the hall sequence for 
               trapezoidal commutation. */
            pData->ovrDataOutPWM3[pData->hallSector] = bldcVector3[pData->vector];
            pData->ovrDataOutPWM2[pData->hallSector] = bldcVector2[pData->vector];
            pData->ovrDataOutPWM1[pData->hallSector] = bldcVector1[pData->vector];
            
            /* Increment Vector index for next voltage vector. */
            pData->vector++; 
            
            pData->intervalCount = 0;
        }
    }
    else
    {
        pData->vector = 0;
        /* Indicates the execution is completed.  */
        pData->executionFlag = 1; 
        /* Disable PWM outputs. */
        HAL_MC1PWMDisableOutputs(); 
    }

}

