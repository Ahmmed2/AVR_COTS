/*
 * Seven_Segment_Program.c
 *
 * Created: 9/15/2023 9:09:22 AM
 *  Author: Ahmed
 */ 



#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "DIO_Interface.h"
#include "DIO_Config.h"

#include "Seven_Segment_Interface.h"
#include "Seven_Segment_Config.h"


u8 BCD_Pins[4] = {PIN0_ID,PIN1_ID,PIN2_ID,PIN4_ID} ;
u8 Seg_Port[4] = {PORTB_ID , PORTB_ID , PORTA_ID , PORTA_ID } ; 
u8 Seg_pin [4]=	 {PIN6_ID,PIN5_ID,PIN2_ID,PIN3_ID};
void SevenSegment_voidInit (void )
{
	
	/* To Choose which 7-Segment Works */  
	DIO_voidSetPinDirection(FIRST_7_SEG_PORT,FIRST_7_SEG_PIN   ,PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(SECOND_7_SEG_PORT,SECOND_7_SEG_PIN ,PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(THIRD_7_SEG_PORT,THIRD_7_SEG_PIN   ,PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(FOURTH_7_SEG_PORT,FOURTH_7_SEG_PIN ,PIN_OUTPUT_ID);
	
	/* Disable All Seven Segment */ 
	DIO_voidSetPinValue(FIRST_7_SEG_PORT,FIRST_7_SEG_PIN ,  PIN_HIGH);
	DIO_voidSetPinValue(SECOND_7_SEG_PORT,SECOND_7_SEG_PIN ,PIN_HIGH);
	DIO_voidSetPinValue(THIRD_7_SEG_PORT,THIRD_7_SEG_PIN   ,PIN_HIGH);
	DIO_voidSetPinValue(FOURTH_7_SEG_PORT,FOURTH_7_SEG_PIN ,PIN_HIGH);
	 
	 /////////////////////////////////////////////////////////
	
	/* BCD Pins */ 
	DIO_voidSetPinDirection(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN1,PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN2,PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN3,PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN4,PIN_OUTPUT_ID);


}

void SevenSegment_voidDisplay(u8 Copy_u8Number,u8 Copy_u8Seg_Number)
{
	
	u8 Local_u8Temp = 0 ;
	switch (Copy_u8Seg_Number)
	{
		case (FIRST_7_SEG):	  DIO_voidSetPinValue(FIRST_7_SEG_PORT,FIRST_7_SEG_PIN ,PIN_LOW);				    break ;
		case (SECOND_7_SEG):  DIO_voidSetPinValue(SECOND_7_SEG_PORT,SECOND_7_SEG_PIN ,PIN_LOW);					break ;
		case (THIRD_7_SEG):	  DIO_voidSetPinValue(THIRD_7_SEG_PORT,THIRD_7_SEG_PIN   ,PIN_LOW);					break ;
		case (FOURTH_7_SEG):  DIO_voidSetPinValue(FOURTH_7_SEG_PORT,FOURTH_7_SEG_PIN ,PIN_LOW);					break ;
	}																						  
	
	
	//_delay_ms(500);

	Local_u8Temp = Get_bit(Copy_u8Number,0);
	DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN1,Local_u8Temp);
	Local_u8Temp = Get_bit(Copy_u8Number,1);
	DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN2,Local_u8Temp);
	Local_u8Temp = Get_bit(Copy_u8Number,2);
	DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN3,Local_u8Temp);
	Local_u8Temp = Get_bit(Copy_u8Number,3);
	DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,SEVEN_SEGMENT_PIN4,Local_u8Temp);
	
}


void SevenSegment_voidCount()
{
	u8 Local_u8LoopCounter = 0 ; 
	u8 Local_u8Temp = 0 ;
	
	/* Fourth Seven Segment */ 
	DIO_voidSetPinValue(FOURTH_7_SEG_PORT,FOURTH_7_SEG_PIN ,PIN_LOW);	
	for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter <= 9 ; Local_u8LoopCounter++)
	{
		Local_u8Temp = Get_bit(Local_u8LoopCounter,0);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[0],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,1);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[1],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,2);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[2],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,3);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[3],Local_u8Temp);
		_delay_ms(1000);
		
		
	}
	
		/* Disable Fourth Seven Segment */ 
		DIO_voidSetPinValue(FOURTH_7_SEG_PORT,FOURTH_7_SEG_PIN ,PIN_HIGH);
		_delay_ms(1000);
	
	
	
	/* Second Seven Segment */ 
	DIO_voidSetPinValue(THIRD_7_SEG_PORT,THIRD_7_SEG_PIN ,PIN_LOW);	
	for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<9 ; Local_u8LoopCounter++)
	{
			Local_u8Temp = Get_bit(Local_u8LoopCounter,0);
			DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[0],Local_u8Temp);
			Local_u8Temp = Get_bit(Local_u8LoopCounter,1);
			DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[1],Local_u8Temp);
			Local_u8Temp = Get_bit(Local_u8LoopCounter,2);
			DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[2],Local_u8Temp);
			Local_u8Temp = Get_bit(Local_u8LoopCounter,3);
			DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[3],Local_u8Temp);
			_delay_ms(1000);
			
		
	}
		/* Disable Third Seven Segment */ 
		DIO_voidSetPinValue(THIRD_7_SEG_PORT,THIRD_7_SEG_PIN ,PIN_HIGH);
		_delay_ms(1000);
	
	
	
	/* Third Seven Segment */ 
	DIO_voidSetPinValue(SECOND_7_SEG_PORT,SECOND_7_SEG_PIN ,PIN_LOW);	
	for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<9 ; Local_u8LoopCounter++)
	{
		Local_u8Temp = Get_bit(Local_u8LoopCounter,0);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[0],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,1);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[1],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,2);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[2],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,3);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[3],Local_u8Temp);
		_delay_ms(1000);
	}
	
	/* Disable Second Seven Segment */ 
	 DIO_voidSetPinValue(SECOND_7_SEG_PORT,SECOND_7_SEG_PIN ,PIN_HIGH);
	_delay_ms(1000);
	
	
	
	/* Fourth Seven Segment */ 
	 DIO_voidSetPinValue(FIRST_7_SEG_PORT,FIRST_7_SEG_PIN ,PIN_LOW);
	 for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<9 ; Local_u8LoopCounter++)
	 {
		Local_u8Temp = Get_bit(Local_u8LoopCounter,0);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[0],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,1);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[1],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,2);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[2],Local_u8Temp);
		Local_u8Temp = Get_bit(Local_u8LoopCounter,3);
		DIO_voidSetPinValue(SEVEN_SEGMENT_PORT,BCD_Pins[3],Local_u8Temp);
		_delay_ms(1000);
	 }
	 /* Disable First Seven Segment */ 
	  DIO_voidSetPinValue(FIRST_7_SEG_PORT,FIRST_7_SEG_PIN ,PIN_HIGH);
		_delay_ms(1000);
}



/* This Function TO write certain Number on 7-Segment at the same time */ 
void SevenSegment_voidWriteNumber(u32 Copy_u8Number)

{
	u8 Local_u8Temp = 0 ; 
	u8 Local_u8LoopCounter = 0 , Local_u8Index = 0  ;
	u8 Local_u8Numbers[4] ;
    
	/* Convert Number to digits */ 
	while  (Copy_u8Number != 0 )
	{
		Local_u8Temp  = Copy_u8Number % 10 ;
		Copy_u8Number = Copy_u8Number / 10 ;
		Local_u8Numbers[Local_u8LoopCounter] = Local_u8Temp ;
		Local_u8LoopCounter++ ;
		
	}
	
	Local_u8LoopCounter-- ;
	
	/*Display Number By Number on each 7-Segment */ 
	for (Local_u8Index = 0 ; Local_u8Index < 4 ; Local_u8Index++)
	{
		SevenSegment_voidDisplay(Local_u8Numbers[Local_u8LoopCounter],Local_u8Index+1);
		_delay_ms(4);
		DIO_voidSetPinValue(Seg_Port[Local_u8Index] , Seg_pin [Local_u8Index] , PIN_HIGH);
		Local_u8LoopCounter -- ; 
	}

}