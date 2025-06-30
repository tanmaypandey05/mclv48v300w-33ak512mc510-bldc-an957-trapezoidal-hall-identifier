// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file hall_sensor.h
 *
 * @brief This is the manual driver header file for the Hall sensor driver
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

#ifndef HALL_SENSOR_H
#define	HALL_SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
    
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
    
#include "port_config.h"
#include "clc1.h"
#include "sccp1.h"
#include "hall_sensor_types.h"

// </editor-fold> 
    
// <editor-fold defaultstate="expanded" desc="DEFINITIONS/CONSTANTS ">

/* Enter the pins to read hall value, value = Hall_3 , Hall_2, Hall_1 */
/* Reads the value of LSB */
#define HALL_1_GetValue()         M1_HALL_A
/* Reads the value */
#define HALL_2_GetValue()         M1_HALL_B
/* Reads the value of MSB */
#define HALL_3_GetValue()         M1_HALL_C

#define MC1_HallSensor_Interrupt              _CCP1Interrupt
#define MC1_HallSensor_Interrupt_FlagClear    CCP1_InterruptFlagClear
#define HallModuleEnable                      CLC1_ModuleEnable     
#define HallModuleDisable                     CLC1_ModuleDisable
#define HallStateChangeTimerDataRead          SCCP1_TimerDataRead    
#define HallStateChangeTimerStart             SCCP1_Timer_Start
#define HallStateChangeTimerStop              SCCP1_Timer_Stop
     
// </editor-fold> 

// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
void MCAPP_HallSensorInit(MCAPP_HALL_SENSOR_T *);
uint16_t MCAPP_HallSensorRead(MCAPP_HALL_INPUT_T *);
void MCAPP_HallSensorValue(MCAPP_HALL_SENSOR_T *);
void MCAPP_MeasureSpeed(MCAPP_HALL_SENSOR_T *);
void HallSensorEnable(void);
void HallSensorDisable(void);
void HallSensorHandler(MCAPP_HALL_SENSOR_T *);
    
// </editor-fold>
#ifdef	__cplusplus
}
#endif

#endif	/* HALL_SENSOR_H */

