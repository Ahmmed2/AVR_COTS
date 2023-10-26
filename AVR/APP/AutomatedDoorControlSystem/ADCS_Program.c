/*
 * ADCS_Program.c
 *
 * Created: 9/24/2023 7:29:44 PM
 *  Author: Ahmed
 */ 

#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "DIO_Config.h"
#include "DIO_Interface.h"
#include "TR_Config.h"
#include "TR_Interface.h"

#include "KEYPAD_Config.h"
#include "KEYPAD_Interface.h"
#include "LCD_Config.h"
#include "LCD_INTERFACE.h"
#include "Servo_Config.h"
#include "Servo_Interface.h"


#include "ADCS_Private.h"
#include "ADCS_Config.h"
#include "ADCS_Interface.h"





void ADCS_voidInit ()
{
	
	DIO_voidSetPinDirection(RED_PORT,RED_PIN,PIN_OUTPUT_ID) ;
	DIO_voidSetPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT_ID) ;
	// OCR1A
	DIO_voidSetPinDirection(PORTD_ID,PIN5_ID,PIN_OUTPUT_ID);
	TMR1_voidInit(FASTPWM_MODE14,OCR1A_PIN,OC_CLEAR) ;
	// Door Closed
	Servo_voidGetAngle(-90);
	TMR1_voidPreScaler (DIV64) ;

}

void ADCS_SystemStart()
{
	u8 Local_u8Password[10],Local_u8InputPass[10] ;
	u8 Local_u8LoopCounter = 0 ,Local_u8LoopCounter2 = 0   ;
	u16 Local_u8Temp = 0 ;
	u8 Local_u8Cont = 0 ,Local_u8WrongTrials = 0;
	u8 static Local_u8Flag = 0 ; 
		
		
		
	LCD_voidWriteSting("Welcome Home :D  ",LINE1) ; 
	_delay_ms(1000) ; 
	LCD_voidClear() ;
	_delay_ms(100);
	LCD_voidWriteSting("Password:",LINE1) ;
	LCD_GoToXY(LINE2,OFFSET0) ;  
	
	
while (Local_u8LoopCounter2 < MAX_TRIALS && Local_u8Flag != PASSWORD_SIZE)
{
	Local_u8Flag = 0 ;
	Local_u8Temp = PASSWORD ;
	ADCS_voidGetPassword(Local_u8Password) ;
	
	for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<PASSWORD_SIZE ; Local_u8LoopCounter++)
	{	
		Local_u8Cont = Local_u8Temp % 10 ;
		Local_u8Temp = Local_u8Temp / 10 ;
		Local_u8InputPass[Local_u8LoopCounter] = Local_u8Cont ;	
	}
	

	for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<PASSWORD_SIZE ; Local_u8LoopCounter++)
	{	

	if (Local_u8InputPass[Local_u8LoopCounter] == Local_u8Password[PASSWORD_SIZE-1-Local_u8LoopCounter] )
	  {
		  Local_u8Flag ++ ;
		  if (Local_u8Flag==PASSWORD_SIZE)
		  {
			LCD_voidClear() ; 
			_delay_ms(50);
			LCD_voidWriteSting("Door is Opening ",LINE1) ; 
			_delay_ms(1000);
			
			/* Servo Door Open */
			Servo_voidGetAngle(90);
			LCD_voidClear() ;
			_delay_ms(50);
			LCD_voidWriteSting("Door is open",LINE1) ;
			_delay_ms(1000);

		  }
	  }
	else 
	  {
		 Local_u8WrongTrials++ ;
		LCD_voidClear() ;
		_delay_ms(150);
		LCD_voidWriteSting("Wrong Password",LINE1) ;
		_delay_ms(500) ;
		LCD_voidWriteSting("Try Again!",LINE2) ;
		_delay_ms(1000);
		break ;
	  }
		
	}
	Local_u8LoopCounter2 ++ ;
	
}


if (Local_u8WrongTrials == MAX_TRIALS)
{
	LCD_voidClear() ;
	_delay_ms(150);
	LCD_voidWriteSting("Out Of Trials ",LINE1) ;
	DIO_voidSetPinValue(BUZZER_PORT,BUZZER_PIN,PIN_HIGH) ;
	DIO_voidSetPinValue(RED_PORT,RED_PIN,PIN_HIGH) ;
}

	
}


void ADCS_voidGetPassword(u8 Local_u8Password[])
{
	/* Array Index */
	u8 Local_u8Index = 0 , Local_u8Flag = 0 , Local_u8keypad_press = 0 ;
	LCD_voidClear() ;
	_delay_ms(150);
	LCD_voidWriteSting("Password:",LINE1) ;
	_delay_ms(150) ;
	LCD_GoToXY(LINE2,OFFSET0) ;
	
	while (Local_u8Flag == 0)
	{
		
		Local_u8keypad_press = KeyPad_u8GetPressedKey();
		
		/* Check if Key is pressed */
		if ( (Local_u8keypad_press != 0xFF) && (Local_u8keypad_press >= 0) && (Local_u8keypad_press < 10)  )
		{	Local_u8Password[Local_u8Index] = Local_u8keypad_press ;
			LCD_voidSendDATA_4L('*') ;
			Local_u8Index++ ;
		}

		/*To Shut down the Keypad */
		else if (Local_u8keypad_press == TERMINATE)
		{
			
			LCD_voidClear();
			_delay_ms(150);
			LCD_voidWriteSting("Checking",LINE1) ;
			_delay_ms(500);
			Local_u8Flag = 1 ;
		}
		
	}
	
}