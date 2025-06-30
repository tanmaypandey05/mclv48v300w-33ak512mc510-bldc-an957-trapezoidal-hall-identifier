// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * hall_sensor.c
 *
 * This file includes subroutine to configure and read Hall value.
 * 
 * 
 * Component: HALL SENSOR
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

// <editor-fold defaultstate="collapsed" desc="Header Files ">

#include <xc.h>
#include <stdint.h>
#include <math.h>
#include "hall_sensor.h"
#include "mc1_user_params.h"
#include "filter.h"
// </editor-fold> 

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: MCAPP_HallSensorInit(&pHallsensor) </B>
*
* @brief Function to initialize Hall sensor 
*        
* @param Pointer to the data structure containing hall sensor parameters.
* @return none.
* 
* @example
* <CODE> MCAPP_HallSensorInit(&pHallsensor); </CODE>
*
*/
void MCAPP_HallSensorInit(MCAPP_HALL_SENSOR_T *pHallsensor)
{
    pHallsensor->calculateSpeed.avgPeriod   = 0;
    pHallsensor->calculateSpeed.speed       = 0;
    pHallsensor->calculateSpeed.period      = 0;
    pHallsensor->calculateSpeed.previousTimerValue = 0;
    pHallsensor->calculateSpeed.presentTimerValue  = 0;
    pHallsensor->calculateSpeed.timerValue  = 0;
    pHallsensor->hallChangeDetected         = 0;
    pHallsensor->value                      = 0;
    pHallsensor->presentValue               = 0;
    pHallsensor->previousValue              = 0;
}

/**
* <B> Function: MCAPP_HallSensorRead(&pHallInput) </B>
*
* @brief Function to read hall sensor value.
*        
* @param Pointer to the data structure containing hall input parameters.
* @return hall sector value.
* 
* @example
* <CODE> MCAPP_HallSensorRead(&pHallInput); </CODE>
*
*/
uint16_t MCAPP_HallSensorRead(MCAPP_HALL_INPUT_T *pHallInput)
{
    /* Read Hall sensor inputs */
    pHallInput->hall_1 = HALL_1_GetValue();
    pHallInput->hall_2 = HALL_2_GetValue();
    pHallInput->hall_3 = HALL_3_GetValue();
    
    pHallInput->hallValue = (pHallInput->hall_3 << 2)|
            (pHallInput->hall_2 << 1)|(pHallInput->hall_1);
    
    return pHallInput->hallValue;
}

/**
* <B> Function: MCAPP_HallSensorValue(&pHallSensor) </B>
*
* @brief Function to read hall sensor value.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MCAPP_HallSensorValue(&pHallSensor); </CODE>
*
*/
void MCAPP_HallSensorValue(MCAPP_HALL_SENSOR_T *pHallSensor)
{
    pHallSensor->presentValue = MCAPP_HallSensorRead(&pHallSensor->hallInput);
    
    pHallSensor->value = pHallSensor->presentValue;
    if(pHallSensor->presentValue != pHallSensor->previousValue)
    {
        pHallSensor->value = pHallSensor->presentValue;
        pHallSensor->previousValue = pHallSensor->value;
        
        if(pHallSensor->hallChangeDetected == 0)
        {
            pHallSensor->hallChangeDetected = 1;
        }
        else
        {
            pHallSensor->hallChangeDetected = 0;
        }
    }
    else
    {
       pHallSensor->value = pHallSensor->value;
       pHallSensor->previousValue = pHallSensor->previousValue;
       pHallSensor->hallChangeDetected = 0;
    }
}

/**
* <B> Function: MCAPP_MeasureSpeed(&pHallSensor) </B>
*
* @brief Function to calculate speed using hall sensor feedback.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MCAPP_MeasureSpeed(&pHallSensor); </CODE>
*
*/ 
void MCAPP_MeasureSpeed(MCAPP_HALL_SENSOR_T *pHallSensor)
{   
    MCAPP_CALC_SPEED_T *pCalculateSpeed = &pHallSensor->calculateSpeed;
    
    /* Calculating Speed using the period */
    if(pCalculateSpeed->startFlag == 1)
    {
       /* Calculating Moving Average of Period */
        pCalculateSpeed->avgPeriod = MCAPP_MovingAvgFilter(pCalculateSpeed->period);
        /* Calculating Speed using the period*/
        if(pCalculateSpeed->avgPeriod != 0)
        {
            pCalculateSpeed->speed = 
                    ((float)pCalculateSpeed->multiplier/pCalculateSpeed->avgPeriod);
        }
        pCalculateSpeed->startFlag = 0;
    }
    /* Stall detection 
     * At lower speeds, the time interval for detecting change is decremented,
     *  to determine whether the motor has stalled or is operating below 
     * the minimum speed threshold 
     * If the motor stalled is detected then the measured speed value is decremented */
    if(pHallSensor->motorStallCounter == 0)
    {
        pCalculateSpeed->speed = pCalculateSpeed->speed - 1;
        if(pCalculateSpeed->speed < 0)
        {
            pCalculateSpeed->speed = 0;
        }
    }
    else
    {
        pHallSensor->motorStallCounter--;
    }
    
}

/**
* <B> Function: HallSensorEnable(void) </B>
*
* @brief Function to enable Hall sensor module.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> HallSensorEnable(); </CODE>
*
*/ 
void HallSensorEnable(void)
{
    /* Enable Hall module */
    HallModuleEnable(); 
    /* Starting the timer*/
    HallStateChangeTimerStart();
}

/**
* <B> Function: HallSensorDisable(void) </B>
*
* @brief Function to disable Hall sensor module.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> HallSensorDisable(); </CODE>
*
*/ 
void HallSensorDisable(void)
{
    /* Disable Hall module */
    HallModuleDisable(); 
    /* Stop the timer*/
    HallStateChangeTimerStop();
    
}

/**
* <B> Function: HallSensorHandler(void) </B>
*
* @brief This Function performs the following actions:
*        (1) Read the Hall sensor value
*        (2) Checks for Change in Hall sector 
*        (3) For a change in sector read the Timer value
*        (4) Use the timer value for speed measurement
*        (5) Check for incorrect Hall sector values and Timer Failure   
*        
* @param none.
* @return none.
* 
* @example
* <CODE> HallSensorHandler(); </CODE>
*
*/ 
void HallSensorHandler(MCAPP_HALL_SENSOR_T *pHallSensor)
{
    MCAPP_CALC_SPEED_T *pCalculateSpeed = &pHallSensor->calculateSpeed;
    
    /* Update the Hall pattern */
    MCAPP_HallSensorValue(pHallSensor);
    /* Check if the Hall change is detected */
    if(pHallSensor->hallChangeDetected == 1)
    {
        /* Store the SCCP Timer Count */
        pCalculateSpeed->presentTimerValue = HallStateChangeTimerDataRead();
        
        pCalculateSpeed->timerValue = pCalculateSpeed->presentTimerValue - 
                                            pCalculateSpeed->previousTimerValue;
        pCalculateSpeed->previousTimerValue = pCalculateSpeed->presentTimerValue;
        
        /* If timer value is rolled over */
        if(pCalculateSpeed->timerValue < 0)
        {
            pCalculateSpeed->period = 0xFFFFFFFF - 
                                                    pCalculateSpeed->timerValue;
        }
        else
        {
            pCalculateSpeed->period = pCalculateSpeed->timerValue;
        }

        /* Incorrect timer value */
        if(pCalculateSpeed->timerValue == 0)
        {
            pHallSensor->timerError = 1;
        }
        /*  Hall malfunction detection: check if the hall state is 
          0 or 7 and enable Hall failure flag */
        if((pHallSensor->value > 0)&&(pHallSensor->value < 7))
        {
            pHallSensor->hallFailure = 0;
            pHallSensor->sector = pHallSensor->value ;
        }
        else
        {
            pHallSensor->hallFailure = 1;
        }
            
        /* The start flag is set for speed calculation based on timer period */
        pHallSensor->calculateSpeed.startFlag = 1;
        /*  Set the motor stop counter value */
        pHallSensor->motorStopCounter = pHallSensor->motorStopValue;
        /* Set the motor stall counter value */
        pHallSensor->motorStallCounter = pHallSensor->motorStallValue;
        /* Hall Change detection flag is cleared */
        pHallSensor->hallChangeDetected = 0;
    }
}