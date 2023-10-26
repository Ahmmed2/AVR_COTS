/*
 * DcMotor_Program.c
 *
 * Created: 9/21/2023 1:15:04 PM
 *  Author: Ahmed
 */ 

#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

///////////////////////////////////////////////

#include "DcMotor_Private.h"
#include "DcMotor_Config.h"
#include "DcMotor_Interface.h"
#include "DIO_Config.h"
#include "DIO_Interface.h" 
#include "TR_Config.h"
#include "TR_Interface.h"


void DcMotor_voidSetDirection_Speed (u8 Copy_u8Direction , u8 Copy_u8Speed ) 
{
	 	/* PWM */
	 	DIO_voidSetPinDirection(DRIVER_PORT,PWM_PIN,OUTPUT_HIGH);
	 	/* DIR */
	 	DIO_voidSetPinDirection(DRIVER_PORT,DIR_PIN,OUTPUT_HIGH);
	 	/* EN */
	 	DIO_voidSetPinDirection(DRIVER_PORT,EN_PIN,OUTPUT_HIGH);
		DIO_voidSetPinValue(DRIVER_PORT,EN_PIN,PIN_HIGH);
		 
// 		 u8 Local_u8Duty = 0 ;
// 		 Local_u8Duty = TMR_voidMappingSpeed (Copy_u8Speed) ;
		 
		 switch (Copy_u8Direction) 
		 {
			 
			 case (CW)   :  
	
							DIO_voidSetPinValue(DRIVER_PORT,DIR_PIN,PIN_HIGH);		
							break ;
			 
			 case (CCW)  :	DIO_voidSetPinValue(PORTB_ID,DIR_PIN,PIN_LOW);		    
							break ;
										
		 }
		 
		 
		TMR0_voidInit(FASTPWM,OC_SET);
		TMR02_voidPreLoad(TIMER0,FASTPWM,Copy_u8Speed) ;
		TMR0_voidPreScaler(DIV64) ;
	
	
}






void DcMotor_voidStopMotor()
{
		TMR0_voidDisable() ;
			
}