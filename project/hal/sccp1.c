// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file sccp1.c
 *
 * @brief This module configures and enables the SCCP1 Module 
 * 
 * Definitions in this file are for dsPIC33AK512MC510
 *
 * Component: SCCP1
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

#include "sccp1.h"
// </editor-fold> 

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: SCCP1_Timer_Initialize() </B>
*
* @brief Function configures SCCP1 Module in 32bit timer mode
*        
* @param none.
* @return none.
* 
* @example
* <CODE> SCCP1_Timer_Initialize(); </CODE>
*
*/
void SCCP1_Timer_Initialize(void)
{
    /* Set SCCP1 operating OFF */
	CCP1CON1bits.ON = 0;   
    /* Set timebase width (32-bit = 1) */
    CCP1CON1bits.T32 = 1;    
	/* Module operates as an Input Capture peripheral */
	CCP1CON1bits.CCSEL = 1;     
    /* Set mode to 16/32 bit timer mode features to Output Timer Mode */
    CCP1CON1bits.MOD = 0b0000;  
    /* No external synchronization; timer rolls over at FFFFh or matches with the Timer Period register */
    CCP1CON1bits.SYNC = 0b00000;
    /* Set timebase synchronization (Synchronized) */
    CCP1CON1bits.TMRSYNC = 0;   
    /* Set the clock source (Tcy) */
    CCP1CON1bits.CLKSEL = 0b000;
    /* Set the clock pre-scaler */
    CCP1CON1bits.TMRPS = 0b00;  
    /* Set Sync/Triggered mode (Synchronous) */
    CCP1CON1bits.TRIGEN = 0;    
    
    /* CCP1 Control Register 2 */
    /* Input Capture Source Select bits - CLC1 Output*/
    CCP1CON2bits.ICS = 4;
    /* Initialize timer prior to enable module. */
    CCP1TMR = 0x0000;                                       
    
    /* Interrupt Priority set */
    IPC6bits.CCP1IP = 0;        
    /* Clear Interrupt flag */
    IFS1bits.CCP1IF = 0;         
    /* Disable Interrupt */
    IEC1bits.CCP1IE = 0; 
    
    /* Disable CCP/input capture */
    CCP1CON1bits.ON = 0;     
}

void SCCP1_SetTimerPrescaler(uint16_t timerPrescaler)
{
    if(timerPrescaler == 64)
    {
        CCP1CON1bits.TMRPS = SCCP1_CLOCK_PRESCALER_64;
    }
    else if(timerPrescaler == 16)
    {
        CCP1CON1bits.TMRPS = SCCP1_CLOCK_PRESCALER_16;
    }
    else if(timerPrescaler == 4)
    {
        CCP1CON1bits.TMRPS = SCCP1_CLOCK_PRESCALER_4;
    }
    else if(timerPrescaler == 1)
    {
        CCP1CON1bits.TMRPS = SCCP1_CLOCK_PRESCALER_1;
    }  
}

void SCCP1_SetTimerPeriod(uint32_t timerPeriod) 
{ 
    CCP1PR = timerPeriod;             
}

void SCCP1_Timer_Start(void)
{
    /* Start the Timer */
    CCP1CON1bits.ON = true;
    
}

void SCCP1_Timer_Stop(void)
{
    /* Stop the Timer */
    CCP1CON1bits.ON = false;
}

uint32_t SCCP1_TimerDataRead(void) 
{ 
    uint32_t timervalue;

    timervalue =  CCP1TMR;
    return timervalue;
}

void SCCP1_TimerDataSet(uint32_t value) 
{ 
   /* Update the counter values */
    CCP1TMR = value;           
}
