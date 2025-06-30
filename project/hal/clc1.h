// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file clc.h
 *
 * @brief This header file lists the functions and definitions - to configure 
 * and enable CLC Module with Hall inputs 
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


#ifndef CLC_H
#define	CLC_H

#ifdef	__cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">      
#include <xc.h>
#include <stdint.h>
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
void CLC1_Initialize(void);

/**
 * Enables CLC1 module.
 * Summary: Enable CLC1 module.
 * @example
 * <code>
 * CLC1_ModuleEnable();
 * </code>
 */
inline static void CLC1_ModuleEnable(void) 
{
   /* Configurable Logic Cell is enabled and mixing input signals */
   CLC1CONbits.ON = 1;
}

/**
 * Disable CLC1 module.
 * Summary: Disable CLC1 module.
 * @example
 * <code>
 * CLC1_ModuleDisable();
 * </code>
 */
inline static void CLC1_ModuleDisable(void) 
{
   /* Configurable Logic Cell is enabled and mixing input signals */
   CLC1CONbits.ON = 0;
}
// </editor-fold>    
#ifdef	__cplusplus
}
#endif

#endif	/* CLC_H */

