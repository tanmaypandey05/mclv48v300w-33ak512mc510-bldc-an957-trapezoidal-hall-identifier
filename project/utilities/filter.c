// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file filter.c
 *
 * @brief This module implements filers.
 *
 * Component: FILTER
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
#include "filter.h"

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="VARIABLES ">

MCAPP_FILTER_LPF_T lowPassFilter;
MCAPP_FILTER_AVG_T movingAvgFilter;

// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">

/**
* <B> Function: MCAPP_LowPassFilter((input) </B>
*
* @brief Function to implement low pass filter. 
*        
* @param Pointer to the data structure containing variables for LPF.
* @return filtered output.
* 
* @example
* <CODE> MCAPP_LowPassFilter(input); </CODE>
*
*/
float MCAPP_LowPassFilter (float input)
{
    /* Filter input using a first order low-pass filter */
    lowPassFilter.output = lowPassFilter.output + 
            ((input - lowPassFilter.output) * LFP_CUTOFF_FREQUENCY);
    
    return lowPassFilter.output;
}

/**
* <B> Function: MCAPP_MovingAvgFilterInit(input) </B>
*
* @brief Function to initialize moving average filter. 
*        
* @param none.
* @return none.
* 
* @example
* <CODE> MCAPP_MovingAvgFilterInit(input); </CODE>
*
*/
void MCAPP_MovingAvgFilterInit (void)
{
    movingAvgFilter.accumalator = 0;
    movingAvgFilter.mean = 0;
    movingAvgFilter.average = 0;
}

/**
* <B> Function: MCAPP_MovingAvgFilter(input) </B>
*
* @brief Function to implement moving average filter. 
*        
* @param Pointer to the data structure containing variables for filter.
* @return average filter output.
* 
* @example
* <CODE> MCAPP_MovingAvgFilter(input); </CODE>
*
*/
int32_t MCAPP_MovingAvgFilter (int32_t input)
{
    movingAvgFilter.accumalator += input;
    movingAvgFilter.mean = (int32_t)(movingAvgFilter.accumalator >> AVGFILTER_SCALER);
    movingAvgFilter.accumalator -= movingAvgFilter.mean;
    movingAvgFilter.average = movingAvgFilter.mean;
    
    return movingAvgFilter.average;
}

// </editor-fold> 