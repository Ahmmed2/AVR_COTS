/*
 * Servo_Program.c
 *
 * Created: 9/21/2023 12:44:24 PM
 *  Author: Ahmed
 */ 

#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "Servo_Private.h"
#include "Servo_Config.h"
#include "Servo_interface.h"

#include "DIO_Config.h"
#include "DIO_Interface.h"
#include "TR_Config.h"	
#include "TR_Interface.h"


void Servo_voidGetAngle(s8 Copy_u8Angle)
{
	
	/* To adjust the Frequency */ 
	TMR1_voidSetFreq(SERVO_FREQUENCY) ;
	/* To adjust the angle */
	TMR1_voidServoAngleControl(Copy_u8Angle) ;
	
}

void Servo_voidStopServo(void) 
{
	
	TMR1_voidDisable() ;
}