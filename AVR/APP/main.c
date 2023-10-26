/*
 * AVR.c
 *
 * Created: 9/8/2023 12:09:15 PM
 * Author : Ahmed
 */ 



#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

//////////////////////////
#include "DIO_Interface.h"
#include "DIO_Config.h"

#include "EXTINT_Interface.h"
#include "EXTINT_Config.h"

#include "ADC_Interface.h"
#include "ADC_Congif.h"

#include "TR_Interface.h"
#include "TR_Config.h"
#include "TR_Private.h"

#include "UART_Interface.h"
#include "UART_Config.h"

#include "SPI_Config.h"
#include "SPI_Interface.h"

 
//////////////////////////

//////////////////////////
#include "KeyPad_Interface.h"
#include "KeyPad_Config.h"

#include "LCD_INTERFACE.h"
#include "LCD_Config.h"

#include "Seven_Segment_Interface.h"
#include "Seven_Segment_Config.h"

#include "Servo_Config.h"
#include "Servo_interface.h"

#include "DcMotor_Config.h"
#include "DcMotor_Interface.h"

#include "StackBasedCalculator_Interface.h"

//////////////////////////
u32 Media_Player[15] = {NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5,REST} ; 




//Call Back For SPI 
void SPI_Handler (void)
{
	DIO_voidTogglePinValue(YELLOW_PORT,YELLOW_PIN) ; 
	_delay_ms(1000) ;
}




//Call Back for UART 
void UARTTXC_Handler (void)
{
	//LCD_GoToXY(LINE2,OFFSET0);
	//LCD_voidDisplayNumber(11);
	DIO_voidTogglePinValue(YELLOW_PORT,YELLOW_PIN) ;
	//UART_SendData('B') ;
	//_delay_ms(1000) ;
 
}

void UARTRXC_Handler (u8 Copy_u8value)
{
	//LCD_GoToXY(LINE2,OFFSET0);
	//LCD_voidDisplayNumber(11);
	DIO_voidTogglePinValue(BLUE_PORT,BLUE_PIN) ;
	//ch = Copy_u8value ;
	LCD_voidWrite_Data_4L(Copy_u8value) ; 
	_delay_ms(200);
	LCD_voidClear() ; 
	_delay_ms(200) ;
	//UART_SendData('B') ;
	//_delay_ms(1000) ;
	
}

	



/* Call Back for EXTI */ 
/*void EXTI_Handler (void)
{
	
	DIO_voidTogglePinValue(PORTA_ID,PIN5_ID);
}*/

	
void TMR0OF_Handler (void)
{
	
	static u16 Counter = 0 ; 
	Counter ++ ;
	if (Counter == 4883 )
	{
		Counter = 0 ;
		DIO_voidTogglePinValue(YELLOW_PORT,YELLOW_PIN) ;
		TMR02_voidPreLoad(TIMER0,NORMAL_MODE,220) ;
	
	}
	  	
}

void TMR0INTCTC_Handler (void)
{
// 	
// 	static u16 Counter = 0 ;
// 	Counter ++ ;
// 	if (Counter == 4500 )
// 	{
// 		Counter = 0 ;
// 		DIO_voidTogglePinValue(YELLOW_PORT,YELLOW_PIN);
// 		//TR_voidPreLoad(TIMER0,CTC,249);
// 		
// 	}

DIO_voidTogglePinValue(YELLOW_PORT,YELLOW_PIN);
	
}

u16 value ;  

void ADCI_Handler(void)
{
	/* Toggle Led */ 
	DIO_voidTogglePinValue(GREEN_PORT,GREEN_PIN);
	_delay_ms(1000);
	/* Keep Receiving New Values */ 
	value = ADC_u16GetResult(ASYNCHRONUS) ;		
	value = (value*5)/1023 ;
	LCD_voidDisplayNumber(value);
	_delay_ms(2000);
	LCD_voidClear();
	_delay_ms(1000);
}

/* LCD Test */ 
/*
u8 LCD_arr[6] ="Ahmed";
u8 customChar[] = {	0b00000,0b00000,0b00010,0b00100,0b01000,0b00100,0b00010,0b00000};*/

/* ADC Test */ 
u8	ADC_Group [8] ;	
u16 ADC_Result[8]={0} ; 
	
	
int main(void)
{
	
	
	
														/* Calculator Test */ 
/*		KeyPad_voidInit() ; 
		LCD_voidInit() ; 
		LCD_voidClear() ; 
		KeyPad_voidCalculator() ;  
		
*/
		

														/* ADC Test */ 
														
// 	/* ADC Array Initialization */ 	
// 	for (u8 i = 0 ; i < 8 ; i++ )
// 	{
// 		ADC_Group[i] = 10 ; 
// 	}
// 	/* Scan Group using Structure */ 
// 	ADC_Scan Local_ADC ; 
// 	Local_ADC.Channel1 = ADC0 ; 
// 	Local_ADC.Channel2 = ADC1 ;
// 	
// 	
// 	/*Initialization */ 
// 	ADC_voidInit() ; 
// 	LCD_voidInit() ;
// 	LCD_voidClear();	
// 	//ADC_voidSelectChannel(ADC1);
// 	ADC_voidSelectPreScaler(Div128);
// 	
// 	/* ADC Channels want to read */ 
// 	ADC_Group[0] = ADC0 ; 
// 	ADC_Group[1] = ADC1 ; 
// 	
// 	/* ISR Call Back  */
// 	ADCINT_SetCallBack(ADCI_Handler);
// 	
// 	/* ADC Mode  */
// 	//ADC_voidStartConversion(ASYNCHRONUS,FREE_RUNNING_MODE);
// 	ADC_voidScanGroup(ADC_Group,ADC_Result);
// 	//ADC_voidScanGroupStruct(&Local_ADC,ADC_Result);
// 	
// 	//Yellow
// 	DIO_voidSetPinDirection(YELLOW_PORT,YELLOW_PIN,PIN_OUTPUT_ID);
// 	//RED
// 	DIO_voidSetPinDirection(RED_PORT,RED_PIN,PIN_OUTPUT_ID);
// 	//Green 
// 	DIO_voidSetPinDirection(GREEN_PORT,GREEN_PIN,PIN_OUTPUT_ID);
// 	//Blue
// 	DIO_voidSetPinDirection(BLUE_PORT,BLUE_PIN,PIN_OUTPUT_ID);
// 	
// 	/* Global Interrupt Enable */ 
//	EXTINT_voidGloblaIniazlize();
// 
// 	
// 	
// 
// 		while (1)
// 		{
// 				/* Single Mode  */
// 			/*	ADC_voidStartConversion(SINGLE_MODE,0);
//  				value = ADC_u16GetResult(SINGLE_MODE);
//  				value = (value*5)/1023 ;
//  				LCD_voidDisplayNumber(value);
//  				_delay_ms(1000);
//  				LCD_voidClear();
//  				_delay_ms(1000);*/
// 
// 
// 					/* Scan Group Test */ 
// 					
//                value = ADC_Result[0];
// 			   value = (value*5)/1023 ;
// 			   LCD_voidDisplayNumber(value);
// 			   _delay_ms(2000);
// 			   LCD_voidClear();
// 			   _delay_ms(1000);
// 			   
// 			   value = ADC_Result[1];
// 			   //value = (value*5)/1023 ;
// 			   LCD_GoToXY(LINE2,OFFSET0);
// 			   LCD_voidDisplayNumber(value);
// 			   _delay_ms(1000);
// 			   LCD_voidClear();
// 			   _delay_ms(1000);   
// 			   
// 		}
										/* TMR0 OF */ 

/*TMR0INTOF_SetCallBack(TMR0OF_Handler);
DIO_voidSetPinDirection(YELLOW_PORT,YELLOW_PIN,PIN_OUTPUT_ID);
TMR02_voidPreLoad(TIMER0,NORMAL_MODE,220);
TMR0_voidInit(NORMAL_MODE,0);
DIO_voidSetPinValue(YELLOW_PORT,YELLOW_PIN,PIN_HIGH);
EXTINT_voidGloblaIniazlize();
TMR0_voidPreScaler(DIV64);*/

                                        /* TMR0 CRC */ 


/*
TMR0INTCompare_SetCallBack(TMR0INTCTC_Handler);
DIO_voidSetPinDirection(YELLOW_PORT,YELLOW_PIN,PIN_OUTPUT_ID);
EXTINT_voidGloblaIniazlize();
TMR0_voidInit(CTC,OC_DISCONNECTED) ;
TMR02_voidSetDelayUsingCTC (TIMER0 , 1000 ) ;
TMR0_voidPreScaler(DIV64); */


                                                     /* PWM Test for Timer 0 and Timer 2 */ 
											 

/*
DIO_voidSetPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT_ID);
DIO_voidSetPinDirection(PORTD_ID,PIN7_ID,PIN_OUTPUT_ID);

TMR0_voidInit(FASTPWM,OC_SET) ;
TMR02_voidSetDutyCycle (TIMER0,100,OC_SET) ;
TMR0_voidPreScaler(DIV64);

TMR2_voidInit(FASTPWM,OC_SET) ;
TMR02_voidSetDutyCycle (TIMER2,75,OC_CLEAR) ;
TMR2_voidPreScaler(DIV64);
 */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  





													/* Relay Test */ 
													
// DIO_voidSetPinDirection(PORTC_ID,PIN7_ID,OUTPUT_HIGH);
// DIO_voidSetPinValue(PORTC_ID,PIN7_ID,PIN_HIGH);

													/* Motor Driver */ 
													
// 	/* PWM */
// 	DIO_voidSetPinDirection(PORTB_ID,PIN3_ID,OUTPUT_HIGH);
// 	/* DIR */ 
// 	DIO_voidSetPinDirection(PORTB_ID,PIN5_ID,OUTPUT_HIGH);
// 	/* EN */ 
// 	DIO_voidSetPinDirection(PORTB_ID,PIN6_ID,OUTPUT_HIGH);
// 	
// 	DIO_voidSetPinValue(PORTB_ID,PIN3_ID,PIN_HIGH);
// 	DIO_voidSetPinValue(PORTB_ID,PIN5_ID,PIN_HIGH);
// 	DIO_voidSetPinValue(PORTB_ID,PIN6_ID,PIN_HIGH);



													/* Timer 1 Test (On Servo )  */ 
/*
		LCD_voidInit() ;
		DIO_voidSetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_HIGH);
		TMR1_voidInit(FASTPWM_MODE14,OCR1A_PIN,OC_CLEAR) ;
		TMR1_voidSetFreq(50) ;
		TMR1_voidServoAngleControl(45) ;
		TMR1_voidPreScaler (DIV64);
		while (1)
		{
			
			
		}*/
													

													/* Control Motor Speed using Pot ( Task ) */  
// u16 value = 0 ;
// u8 Duty = 0 ;
// LCD_voidInit() ;
// ADC_voidInit() ; 
// ADC_voidSelectChannel(ADC1) ;
// ADC_voidSelectPreScaler(Div128);
// DIO_voidSetPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT_ID);
// TMR0_voidInit(FASTPWM,OC_SET) ;

/*
while(1)
{
		
ADC_voidStartConversion(SINGLE_MODE,0);

value = ADC_u16GetResult(SINGLE_MODE);
/ * Temp Sensor * /
//value = value *0.5 ;
/ * VR * /
LCD_voidDisplayNumber(value);
_delay_ms(1000);
LCD_voidClear() ;
_delay_ms(1000);
value = (value*5)/1024 ;
LCD_voidDisplayNumber(value);
_delay_ms(1000);
LCD_voidClear() ;
_delay_ms(1000);
Duty = TMR_voidMappingSpeed(value) ;
LCD_GoToXY(LINE2,OFFSET0);
LCD_voidDisplayNumber(Duty);
_delay_ms(1000);
LCD_voidClear() ;
_delay_ms(1000);
TMR02_voidSetDutyCycle (TIMER0,Duty,OC_SET) ;
TMR0_voidPreScaler(DIV64);
	
}
	*/	
	
																		/* Control Servo using drivers */ 

/*
DIO_voidSetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_HIGH);
TMR1_voidInit(FASTPWM_MODE14,OCR1A_PIN,OC_CLEAR) ;		
Servo_voidGetAngle(-45) ; 
TMR1_voidPreScaler (DIV64) ;*/	

																		/* Phase Correct Mode Check Timer 0 */ 
/*
DIO_voidSetPinDirection(PORTB_ID , PIN3_ID , OUTPUT_HIGH );
TMR0_voidInit(PHASE_CORRECT , OC_SET ) ;
TMR02_voidPreLoad (TIMER0 , PHASE_CORRECT ,50 ) ;
TMR0_voidPreScaler(DIV64) ;
*/

																		/* DC Motor Test using Driver */ 
																		
/*
DcMotor_voidSetDirection_Speed(CCW,20) ;
_delay_ms(2000)	;
DcMotor_voidSetDirection_Speed(CCW,100) ;
_delay_ms(2000)	;
*/										



																	/* Stack Based Calculator */ 
																	
																	

 /*	 KeyPad_voidInit() ;	
 	 LCD_voidInit() ;		
 	 StackBasedCalculator_voidShowInput() ;				

*/
	 
	 
	 
	                                                             /* Media Player */ 
//  LCD_voidInit();
//  DIO_voidSetPinDirection(PORTD_ID,PIN5_ID,OUTPUT_HIGH)  ;
//  DIO_voidSetPinDirection(PORTC_ID,PIN6_ID,PIN_INPUT_ID) ;			 
//  TMR1_voidInit(FASTPWM_MODE14 , OCR1A_PIN , OC_SET) ;
//  TMR1_voidSetFreq (Media_Player[0])	;
//  TMR1_voidPreScaler(DIV64);
// 
// //for (u8 i=0 ; i<15 ; i++)
// //{
// 
// TMR1_voidSetDutyDependonICR1 (50)   ; 
// //}
// 



														/* UART Test */ 
														 
// u8 ch = 'A' ;	
// LCD_voidInit();
// DIO_voidSetPinDirection(YELLOW_PORT,YELLOW_PIN,OUTPUT_HIGH) ;
// DIO_voidSetPinDirection(PORTD_ID,PIN1_ID,OUTPUT_HIGH) ;
// // UARTTXC_SetCallBack(UARTTXC_Handler) ;
// // UARTRXC_SetCallBack(UARTRXC_Handler) ;
// // EXTINT_voidGloblaIniazlize() ;
// UART_voidInialize() ;
// u8 arr[8] = {0} ;
// 
// 
// 
// while(1)
// {
// 	if (ch != '\0' && ch!='\r' && ch!='\n' )
// 	{
// 	UART_voidSendString("HELLO") ;
// 	//UART_SendData('A') ;
// 	_delay_ms(200);
// 	}
//   	ch = UART_ReceiveData() ;
// 	// UART_voidReceiveString(arr) ;
// 
// 	 if (ch != '\0' && ch!='\r' && ch!='\n')
// {  	LCD_voidWrite_Data_4L(ch);
//   	_delay_ms(200);
//   	LCD_voidClear() ;
//   	_delay_ms(200);
// }
// 	
// }




										/* SPI Test */ 
		
	DIO_voidSetPinDirection(YELLOW_PORT,YELLOW_PIN,PIN_OUTPUT_ID) ;	
	//SS
	DIO_voidSetPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT_ID);
	DIO_voidSetPinValue(PORTB_ID,PIN4_ID,PIN_LOW);
	// MOSI 
	DIO_voidSetPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT_ID);
	//MISO
	DIO_voidSetPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT_ID);
	//Clock
	DIO_voidSetPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT_ID);	
	
	SPI_SetCallBack(SPI_Handler) ;							 									
	SPI_voidInialize() ;
	EXTINT_voidGloblaIniazlize() ;

	while (1)
	{
			SPI_voidTransmiter('A') ;

	}


											/* SPI Communicate with LCD */ 
											
		
/*
	
		
		//MOSI
		DIO_voidSetPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT_ID);
		//MISO
		DIO_voidSetPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT_ID);
		//CLK
		DIO_voidSetPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT_ID);
		//ST_CP
		DIO_voidSetPinDirection(PORTA_ID,PIN7_ID,PIN_OUTPUT_ID) ;
		
		SPI_voidInialize(MASTER) ;
    	/ * Led Initialize using IC * /
    	LCD_voidInit_IC() ;
		

	
		while (1)
		{
			LCD_voidWriteDataIC_4L('a') ;
			_delay_ms(1000) ; 
			LCD_voidClearIC_4L () ; 
			_delay_ms(1000) ; 
		}*/
		
		
	
return 0 ;

}


