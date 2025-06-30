// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * hall.h
 *
 * This header file lists data type definitions and interface functions of the
 * Hall and Phase sequence identification
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

#ifndef __HALL_H
#define __HALL_H

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>     // include processor files - each processor file is guarded. 
#include "board_service.h"
#include "hall_identifier_types.h"
#include "hall_sensor.h"
#include "mc1_user_params.h"

// </editor-fold>

#ifdef __cplusplus  // Provide C++ Compatability
    extern "C" {
#endif

// <editor-fold defaultstate="expanded" desc="TYPE DEFINITIONS ">

/** PI coefficients for current control of hall sequence identifier */        
#define HALLSEQ_CURRENT_KP          0.8f
#define HALLSEQ_CURRENT_KI          0.003f
#define HALLSEQ_CURRENT_OUTMAX      0.9f
        
/** Set the CURRENT LIMIT in Amps
*
* Current limit is set in Ampere to limit the current applied to the motor 
* during the hall sequence identification process. 
* The value for current limit is set to 10% to 30% of the motor rated current. 
* 
*/
#define HALLSEQ_CURRENT_LIMIT_AMPS 0.5f   
                
/* Set the Voltage VECTOR COMMUTATION INTERVAL
* 
* Specify the VECTOR COMMUTATION INTERVAL in terms ADC ISR cycles (counts).
* This sets the interval between two different voltage vectors applied to the
* motor to determine hall sequence of the motor.
* This interval must be varied depending on the application and motor inertia. 
* In this code the detection function is called in the ADC interrupt which 
* occurs every 50 microseconds.
* e.g. VECTOR_COMMUTATION_INTERVAL(in seconds) = 20,000 * 50 usec = 1 second
*/
#define VECTOR_COMMUTATION_INTERVAL 20000 

/* Hall sectors */
#define HALL_SECTOR 6
// </editor-fold>

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/* Initialize identifier */
void HallSeqIdentifier_Init(MCAPP_HALLSEQ_IDENT_T*, uint32_t);
/* Function to execute hall sequence identifier */
void HallSeqIdentifier_Execute(MCAPP_HALLSEQ_IDENT_T*, float); 

// <editor-fold defaultstate="colapsed" desc=" VARIABLES ">

// </editor-fold>

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
#endif      // end of __HALL_H
