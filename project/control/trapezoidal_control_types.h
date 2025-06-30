// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file trapezoidal_control_types.h
 *
 * @brief This module initializes data structure variable type definitions of 
 * Trapezoidal control structure and enumerations
 * 
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef __TRAPEZOIDAL_CONTROL_TYPES_H
#define	__TRAPEZOIDAL_CONTROL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <stdint.h>
#include <stdbool.h>
  
// </editor-fold>
    
// <editor-fold defaultstate="collapsed" desc="VARIABLE TYPE DEFINITIONS ">

typedef struct
{
    uint32_t 
        controlLoop,
        targetDuty;
    
    float
        controlInput,
        targetSpeed,
        targetCurrent;
        
} MCAPP_CONTROL_T;

// </editor-fold>

#ifdef __cplusplus
}
#endif

#endif	/* end of __TRAPEZOIDAL_CONTROL_TYPES_H */

