// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file clc.c
 *
 * @brief This module configures and enables the CLC Module with Hall inputs
 * 
 * Definitions in this file are for dsPIC33AK512MC510
 *
 * Component: CLC
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
#include <stdbool.h>

#include "clc1.h"
// </editor-fold> 

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: CLC1_Initialize() </B>
*
* @brief Function configures CLC1 Module to detect change in Hall pattern.
*        
* @param none.
* @return none.
* 
* @example
* <CODE> CLC1_Initialize(); </CODE>
*
*/
void CLC1_Initialize(void)
{
    /* Disable CLC1 module */
    CLC1CONbits.ON = 0;
    
    /* CLC1SEL MUX1 - CLC Input A (PPS CLCINA) */
    CLC1SELbits.DS1 = 4;
    /* CLC1SEL MUX2 - CLC Input B (PPS CLCINC) */
    CLC1SELbits.DS2 = 3;
    /* CLC1SEL MUX3 - CLC Input C (PPS CLCINF) */
    CLC1SELbits.DS3 = 4;
    /* CLC1SEL MUX4 */
    //CLC1SELbits.DS4 = 4;

    /* Gate1 Data (A'+B') */
    /* A' */
    CLC1GLSbits.G1D1N = 1;
    CLC1GLSbits.G1D1T = 0;
    /* B' */
    CLC1GLSbits.G1D2N = 1;
    CLC1GLSbits.G1D2T = 0;
    /* 0 */
    CLC1GLSbits.G1D3N = 0;
    CLC1GLSbits.G1D3T = 0;
    /* 0 */
    CLC1GLSbits.G1D4N = 0;
    CLC1GLSbits.G1D4T = 0;

    /* Gate2 Data (B'+C') */
    /* 0 */
    CLC1GLSbits.G2D1N = 0;
    CLC1GLSbits.G2D1T = 0;
    /* B' */
    CLC1GLSbits.G2D2N = 1;
    CLC1GLSbits.G2D2T = 0;
    /* C' */
    CLC1GLSbits.G2D3N = 1;
    CLC1GLSbits.G2D3T = 0;
    /* 0 */
    CLC1GLSbits.G2D4N = 0;
    CLC1GLSbits.G2D4T = 0;

    /* Gate3 Data (A'+C') */
    /* A' */
    CLC1GLSbits.G3D1N = 1;
    CLC1GLSbits.G3D1T = 0;
    /* 0 */
    CLC1GLSbits.G3D2N = 0;
    CLC1GLSbits.G3D2T = 0;
    /* C' */
    CLC1GLSbits.G3D3N = 1;
    CLC1GLSbits.G3D3T = 0;
    /* 0 */
    CLC1GLSbits.G3D4N = 0;
    CLC1GLSbits.G3D4T = 0;

    /* Gate4 Data (0) */
    /* 0 */
    CLC1GLSbits.G4D1N = 0;
    CLC1GLSbits.G4D1T = 0;
    /* 0 */
    CLC1GLSbits.G4D2N = 0;
    CLC1GLSbits.G4D2T = 0;
    /* 0 */
    CLC1GLSbits.G4D3N = 0;
    CLC1GLSbits.G4D3T = 0;
    /* 0 */
    CLC1GLSbits.G4D4N = 0;
    CLC1GLSbits.G4D4T = 0;

    /* CLC1 Control Register */
    /* The output of Gate 1 logic is inverted when applied to the logic cell */
    CLC1CONbits.G1POL = 0;
    /* The output of Gate 2 logic is inverted when applied to the logic cell */
    CLC1CONbits.G2POL = 0;
    /* The output of Gate 3 logic is inverted when applied to the logic cell */
    CLC1CONbits.G3POL = 0;
    /* The output of Gate 4 logic is inverted when applied to the logic cell */
    CLC1CONbits.G4POL = 1; /* Invert '0' to '1' */

    /* Configurable Logic Cell is four-input AND */
    CLC1CONbits.MODE = 2;

    /* Configurable Logic Cell Port Enable bit */
    CLC1CONbits.LCOE = 0;
    /* Configurable Logic Cell output low */
    CLC1CONbits.LCOUT = 0;
    /* Configurable Logic Cell Output is not inverted */
    CLC1CONbits.LCPOL = 0;

}
