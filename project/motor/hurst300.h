// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file hurst300.h
 *
 * @brief This file has definitions to be configured by the user for spinning
 * motor using field oriented control.
 *
 * Motor : Hurst300 (Hurst DMA0204024B101 or AC300022 or Long Hurst)
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

#ifndef __HURST300_H
#define __HURST300_H

#ifdef __cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <math.h>
#include <stdint.h>

#include "../mc1_user_params.h"
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="DEFINITIONS/CONSTANTS ">
    
/*Parameters of Hurst300 (Hurst DMA0204024B101 : AC300022 : Long Hurst)*/
/** Motor Name Plate Parameters */
/* No.of pole pairs*/
#define POLE_PAIRS                                      5
/* Minimum motor speed at the lowest potentiometer position (unit : RPM)*/
#define MINIMUM_SPEED_RPM                             35.0f
/* Maximum motor speed at the highest potentiometer position (unit : RPM)*/
#define MAXIMUM_SPEED_RPM                             3500.0f
/* Safe speed to change direction (unit : RPM) */
#define DIRECTION_CHANGE_SPEED_RPM                    50.0f
/* Motor Rated Bus Current in RMS (unit : amps) */
#define NOMINAL_CURRENT_BUS_RMS                       3.4f

/*PI Controller Parameters*/    
/* Speed Control Loop - PI Coefficients */
#define SPEEDCNTR_PTERM                               0.00002f
#define SPEEDCNTR_ITERM                               0.0000008f
#define SPEEDCNTR_OUTMAX                              0.999f
#define SPEEDCNTR_OUTMIN                              0.0f

/* Current Control Loop - PI Coefficients */
#define CURRCNTR_PTERM                               0.006f
#define CURRCNTR_ITERM                               0.0001f
#define CURRCNTR_OUTMAX                              0.999f
    
/*Fault parameters*/ 
/* Overcurrent fault limit(comparator and Fault PCI) - bus current (unit : amps)*/
#define OC_FAULT_LIMIT_DCBUS                            7.0f  
    
// </editor-fold>

#ifdef __cplusplus
}
#endif

#endif	/* end of __HURST300_H */
