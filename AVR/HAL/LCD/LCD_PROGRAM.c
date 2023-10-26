
/* LIB Includes */
#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

/* MCAL Includes */
#include "DIO_Interface.h"
#include "DIO_Config.h"

#include "SPI_Config.h"
#include "SPI_Interface.h"



/* HAL Includes */
#include "LCD_Private.h"
#include "LCD_INTERFACE.h"
#include "LCD_Config.h"






	
/* Port B  --> Data Pins */ 
const u8 Data[4] = {D7,D6,D5,D4};
	
	
/* Initialize Command Function */ 
#if LCD_TYPE == Four_BIT

void LCD_voidInit(void)
{ 

#if LCD_TYPE == Eight_BIT

	/* Set Pin Direction*/
	DIO_voidSetPinDirection(PORTB_ID,PIN0_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(PORTB_ID,PIN1_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(PORTB_ID,PIN2_ID, PIN_OUTPUT_ID);
	/*Set Port Direction*/
	DIO_voidSetPortDirection(PORTB_ID,0b11111111);
    
	/* Initialization */
    
	/*Delay 30*/
	_delay_ms(30);
	/*  Function Set*/
	LCD_voidWriteCommand(FUNCTION_SET);
	/*Delay 2*/
	_delay_ms(2);
	/* Display on/off*/
	LCD_voidWriteCommand(DisplayON_OFF);
	/*Delay 2ms*/
	_delay_ms(2);
	/* Clear Display*/
	LCD_voidWriteCommand(CLEAR_DISPLAY);

#endif 


#if LCD_TYPE == Four_BIT

    /* Set Control Pin Direction*/ 
    DIO_voidSetPinDirection(PORTA_ID,RS, PIN_OUTPUT_ID);
    DIO_voidSetPinDirection(PORTA_ID,EN, PIN_OUTPUT_ID);
	
	/* Set Data Pin Direction */
	DIO_voidSetPinDirection(PORTB_ID,PIN4_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(PORTB_ID,PIN2_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(PORTB_ID,PIN1_ID, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(PORTB_ID,PIN0_ID, PIN_OUTPUT_ID);
       
	   
	                              /* Initialization */
								  
	/*Delay 50*/ 
	_delay_ms(50);
	
    /* Send Command Function Set*/
	LCD_voidWriteCommand_4L(FUNCTION_SET_H);
	LCD_voidWriteCommand_4L(FUNCTION_SET_L);
	LCD_voidWriteCommand_4L(FUNCTION_SET_LL);
    /*Delay 50us*/
	_delay_us(50);
	
    /*Send Command Display on/off*/
	LCD_voidWriteCommand_4L(DisplayON_OFF_H);
	LCD_voidWriteCommand_4L(DisplayON_OFF_L);
    /*Delay 50us*/
	_delay_us(50);
	
    /*Send Command Clear Display*/
	LCD_voidWriteCommand_4L(CLEAR_DISPLAY_H);
	LCD_voidWriteCommand_4L(CLEAR_DISPLAY_L);
	/*Delay 2ms*/
	_delay_ms(2);
	
	/*Entry Mode Set */ 
	LCD_voidWriteCommand_4L(ENTRY_MODE_H);
	LCD_voidWriteCommand_4L(ENTRY_MODE_L);
	
	

}
#endif 


/* To let the LCD read the data on Pins */
void LCD_voidEnable_4L()
{
	DIO_voidSetPinValue(CONTROL_PORT,EN,PIN_HIGH);
	_delay_us(50);
	DIO_voidSetPinValue(CONTROL_PORT,EN,PIN_LOW);
}



/* Send the command Not Data on Data Pins from D7-D4 */
void LCD_voidWriteCommand_4L(u8 Copy_u8Value ) 
{
	u8 Local_u8Temp = 0 ; 
	
	DIO_voidSetPinValue(CONTROL_PORT,RS,PIN_LOW);

	 Local_u8Temp = Get_bit(Copy_u8Value,3) ;
 	DIO_voidSetPinValue(DATA_PORT,PIN4_ID,Local_u8Temp);
	 Local_u8Temp = Get_bit(Copy_u8Value,2) ;
 	DIO_voidSetPinValue(DATA_PORT,PIN2_ID,Local_u8Temp);
	 Local_u8Temp = Get_bit(Copy_u8Value,1) ;
 	DIO_voidSetPinValue(DATA_PORT,PIN1_ID,Local_u8Temp);
	 Local_u8Temp = Get_bit(Copy_u8Value,0) ;
 	DIO_voidSetPinValue(DATA_PORT,PIN0_ID,Local_u8Temp);
    LCD_voidEnable_4L();
		


}


/* Send Data not Command on the Data Pins */
void LCD_voidWrite_Data_4L(u8 Copy_u8Value )
{
	

		u8 Local_u8Temp,Local_u8Cont = 0,Local_u8LoopCounter=0 ;
		
		Local_u8Temp = (Copy_u8Value>>4); 
		
		for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<2 ; Local_u8LoopCounter++)
		{
		DIO_voidSetPinValue(CONTROL_PORT,RS,PIN_HIGH);
		Local_u8Cont = Get_bit(Local_u8Temp,3) ;
		DIO_voidSetPinValue(DATA_PORT,PIN4_ID,Local_u8Cont);
		Local_u8Cont = Get_bit(Local_u8Temp,2) ;
		DIO_voidSetPinValue(DATA_PORT,PIN2_ID,Local_u8Cont);
		Local_u8Cont = Get_bit(Local_u8Temp,1) ;
		DIO_voidSetPinValue(DATA_PORT,PIN1_ID,Local_u8Cont);
		Local_u8Cont = Get_bit(Local_u8Temp,0) ;
		DIO_voidSetPinValue(DATA_PORT,PIN0_ID,Local_u8Cont);
		Local_u8Temp = Copy_u8Value ;
		LCD_voidEnable_4L() ;
		}	
}



void  LCD_voidSendDATA_4L(u8 Copy_u8DATA)
{	
		
	/*Send Data*/
	LCD_voidWrite_Data_4L(Copy_u8DATA);
}


#endif 







#if LCD_TYPE == Eight_BIT

void LCD_voidWriteCommand_8L( u8 Copy_u8Command)
{
	/*RS=0--->PortB,pin0*/
    DIO_voidSetPinValue(PORTB_ID, PIN0_ID,PIN_LOW);
	/*RW=0--->PortB,pin1*/
    DIO_voidSetPinValue(PORTB_ID, PIN1_ID,PIN_LOW);
    /*Send Data  Data Pins of LCD ---->PortA*/
   DIO_voidSetPortValue(PORTA_ID,Copy_u8Command);
   /*Enable Pulse--->PortB,Pin2*/
   DIO_voidSetPinValue(PORTB_ID, PIN2_ID,PIN_OUTPUT_ID);
	_delay_ms(2); //1 second delay
   DIO_voidSetPinValue(PORTB_ID, PIN2_ID,PIN_LOW);

}



void  LCD_voidWriteDATA_8L( u8 Copy_u8DATA)
{
	/*RS=1--->pin0*/
    DIO_voidSetPinValue(PORTB_ID, PIN0_ID,PIN_HIGH);
 	/*RW=0--->pin1*/
    DIO_voidSetPinValue(PORTB_ID, PIN1_ID,PIN_LOW);
    /*Send Data*/
    DIO_voidSetPortValue(PORTA_ID,Copy_u8DATA);
	
    /*Enable Pulse*/
    DIO_voidSetPinValue(PORTB_ID, PIN2_ID,PIN_HIGH);
	_delay_ms(2); //1 second delay
    DIO_voidSetPinValue(PORTB_ID, PIN2_ID,PIN_LOW);
	


}


#endif


void LCD_GoToXY(u8 Copy_u8X, u8 Copy_u8Y)
{
		#if (LCD_Type==Eight_BIT)
		
		u8 LOC_Default = DDRAM_BASE_ADDRESS;
		
		//First Line 
		if (Copy_u8X==1)
		{
			LOC_Default = FIRST_LINE_ADDRESS + Copy_u8Y ;
			LCD_voidWriteCommand_8L(LOC_Default);
		}
		
		//Second Line 
		else
		{ 
			LOC_Default = SECOND_LINE_ADDRESS + Copy_u8Y ;

			LCD_voidWriteCommand_8L(LOC_Default);
		}
		
		
		#elif (LCD_Type==Four_BIT)
		
		u8 LOC_Default=DDRAM_BASE_ADDRESS;
		u8 Local_u8Temp = 0 ;
		
		//First Line
		if (Copy_u8X==LINE1)
		{
			LOC_Default= FIRST_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
		}
		
		//Second Line
		else if (Copy_u8X==LINE2)
		{
			LOC_Default= SECOND_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			
		}
		
		//Third Line 
		else if (Copy_u8X==LINE3)
		{
			LOC_Default= THIRD_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
				
		}
		
		//Fourth Line 
		else if (Copy_u8X==LINE4)
		{
			LOC_Default= FOURTH_LINE_ADDRESS + Copy_u8Y;
			Local_u8Temp = LOC_Default >> 4 ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
			Local_u8Temp = LOC_Default ;
			LCD_voidWriteCommand_4L(Local_u8Temp);
					
		}
#endif 
}


/* Write Group of Characters on LCD */
void LCD_voidWriteSting(u8 *Copy_u8string , u8 Copy_u8Line)
{
	
#if (LCD_Type==Eight_BIT)

	u8 Local_u8Shift = 0 ;
	while (Copy_u8string[Local_u8Shift]!='\0')
	{
		LCD_GoToXY(Copy_u8Line,Local_u8Shift);
		LCD_voidWriteDATA_8L(Copy_u8string[Local_u8Shift]);
		Local_u8Shift++;
	}
	
#elif (LCD_Type==Four_BIT)

	u8 Local_u8Shift = 0 ;
	while (Copy_u8string[Local_u8Shift]!='\0')
	{
		LCD_GoToXY(Copy_u8Line,Local_u8Shift);
		LCD_voidSendDATA_4L(Copy_u8string[Local_u8Shift]);
		Local_u8Shift++;
	}

#endif
}


/* Display Numbers on LCD */ 
void LCD_voidDisplayNumber(u32 Copy_u32DATA)
{
	
#if LCD_Type==Eight_BIT

	u8  Local_u32Count = 0 , Local_u32Cont = 0 ;
	s8  Local_s8Index = 0 ;
	u32 Local_u32Numbers[100] ;

	while (Copy_u32DATA != 0)
	{
		Local_u32Cont =  Copy_u32DATA %10 ;
		Copy_u32DATA  =  Copy_u32DATA/10 ;
		Local_u32Numbers[Local_u32Count] = Local_u32Cont ;
		Local_u32Count++ ;
	}

	for (Local_s8Index = (Local_u32Count-1) ; Local_s8Index>=0 ; Local_s8Index--)
	{
		LCD_voidWriteDATA_8L(Local_u32Numbers[Local_s8Index]+48);
	}
	
	
#elif LCD_Type==Four_BIT

	u32  Local_u32Count = 0 ; 
	u8 Local_u8Cont = 0 ;
	s8  Local_s8Index = 0 ;
	u32 Local_u32Numbers[100] ;
	u32 Local_u8Temp = 0 ;


	if (Copy_u32DATA == Local_u8Temp )
	{
		LCD_voidSendDATA_4L(48) ;
	}
	
	else
	{      
		
		while (Copy_u32DATA != 0  )
		{
		Local_u8Cont =  Copy_u32DATA %10 ;
		Copy_u32DATA  =  Copy_u32DATA/10 ;
		Local_u32Numbers[Local_u32Count] = Local_u8Cont ;
		Local_u32Count++ ;
		}


		for (Local_s8Index = (Local_u32Count-1) ; Local_s8Index>=0 ; Local_s8Index--)
		{
		LCD_voidSendDATA_4L(Local_u32Numbers[Local_s8Index]+48) ;
		}
		
}
#endif
}

 


/* Undefined Character in CGROM , and want to display it */ 
void LCD_voidWriteSpecialCharacter(u8 Copy_u32arr[8],u8 Copy_u8Pattern_Number , u8 Copy_u8Line , u8 Copy_u8Offset )
{
	/* We can write 8 Special Character ,each is 8 Byte */
	/* First 8 Byte in the 64 Byte Start at address 64  */
	
#if LCD_Type==Eight_BIT

	u8 Local_Temp = 0 ;
	u8 Local_Loop_Counter = 0 ;
		
	Local_Temp = (CGRAM_BASE_ADDRESS+Copy_u8Pattern_Number*8 );
	LCD_voidWriteCommand_8L(Local_Temp);
	
	for (Local_Loop_Counter =0 ; Local_Loop_Counter < 8 ; Local_Loop_Counter++)
	{
		LCD_voidWriteDATA_8L(Copy_u32arr[Local_Loop_Counter]);
	}
	
	/* Place To Print Special Character In */ 
	LCD_GoToXY(Copy_u8Line,Copy_u8Offset);
	
	/* Pattern Number */ 
	LCD_voidWriteDATA_8L(Copy_u8Pattern_Number);
	
	
#elif LCD_Type==Four_BIT
	
		u8 Local_Temp = 0 ;
		u8 Local_Loop_Counter = 0 ;
		Local_Temp = (CGRAM_BASE_ADDRESS+Copy_u8Pattern_Number*8 ) >> 4 ;
		LCD_voidWriteCommand_4L(Local_Temp);
		Local_Temp = (CGRAM_BASE_ADDRESS+Copy_u8Pattern_Number*8 );
		LCD_voidWriteCommand_4L(Local_Temp);
		
		for (Local_Loop_Counter = 0 ; Local_Loop_Counter<8 ; Local_Loop_Counter++)
		{
			LCD_voidSendDATA_4L(Copy_u32arr[Local_Loop_Counter]);
		}
		
		/* Place To Print Special Character In */
		LCD_GoToXY(Copy_u8Line,Copy_u8Offset);
		/* Pattern Number */
		LCD_voidSendDATA_4L(Copy_u8Pattern_Number);
#endif
}


/* To shift the Cursor Right , Left or Change the Display */ 
void LCD_voidShift(u8 Copy_u8ShifttingDirection)
{
	
	LCD_voidWriteCommand_4L(SHIFTING_H);
	if (Copy_u8ShifttingDirection == RIGHT)
	{
		LCD_voidWriteCommand_4L(SHIFTINGRIGHT_L);
	}
	
	else if (Copy_u8ShifttingDirection == LEFT)
	{
		LCD_voidWriteCommand_4L(SHIFTINGLEFT_L);
	}
	else if (Copy_u8ShifttingDirection == DISPLAY_LEFT)
	{
		LCD_voidWriteCommand_4L(SHIFTING_ENTIRE_DISPLAY_L);
		
	}
	else if (Copy_u8ShifttingDirection == DISPLAY_RIGHT)
	{
		LCD_voidWriteCommand_4L(SHIFTING_ENTIRE_DISPLAY_R);
	}
	
}


/* To Clear LCD */ 
void LCD_voidClear()
{
#if LCD_Type==Eight_BIT
	LCD_voidWriteCommand_8L(CLR_LCD);
	
	
	
#elif LCD_Type==Four_BIT
	LCD_voidWriteCommand_4L(CLR_LCD_H);
	LCD_voidWriteCommand_4L(CLR_LCD_L);
	
#endif	
}





/////////////////////////////////////////////////
	
/* This Function to operate LCD Using IC 74HC595 */


void LCD_voidInit_IC(void)
{
	/* Set Control Pin Direction */
	DIO_voidSetPinDirection(PORTA_ID,RS, PIN_OUTPUT_ID);
	DIO_voidSetPinDirection(PORTA_ID,EN, PIN_OUTPUT_ID);
	
	/*Delay 50*/
	_delay_ms(35);
	
	/* Rs Low */ 
	DIO_voidSetPinValue(PORTA_ID,RS,PIN_LOW);
	/* Send Command Function Set*/

	SPI_voidTransmiter(FUNCTION_SET_H);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;


	SPI_voidTransmiter(FUNCTION_SET_L);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	
	SPI_voidTransmiter(FUNCTION_SET_LL);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	/* Delay 50us */
	_delay_us(50);
	
	
	/* Send Command Display on/off */
	SPI_voidTransmiter(DisplayON_OFF_H);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	
	SPI_voidTransmiter(DisplayON_OFF_L);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	/* Delay 50us */
	_delay_us(50);

	/* Send Command Clear Display */
	SPI_voidTransmiter(CLEAR_DISPLAY_H);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	
	SPI_voidTransmiter(CLEAR_DISPLAY_L);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	/* Delay 2ms */
	_delay_ms(2);
	
	/* Entry Mode Set */
	SPI_voidTransmiter(ENTRY_MODE_H);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	
	SPI_voidTransmiter(ENTRY_MODE_L);
	LCD_EnableICPulse () ;
	LCD_voidEnable_4L() ;
	
	
}

void LCD_EnableICPulse ()
{
	DIO_voidSetPinValue(PORTA_ID, PIN7_ID,PIN_HIGH);
	_delay_us(1); 
	DIO_voidSetPinValue(PORTA_ID, PIN7_ID,PIN_LOW);
	_delay_us(1);
}



void LCD_voidWriteDataIC_4L(u8 Copy_u8Command)
{
	/*RS=1--->pin0 */
	DIO_voidSetPinValue(PORTA_ID,PIN3_ID,PIN_HIGH);
	
	/* Send Data */
	u8 Data = Copy_u8Command >> 4 ;
	SPI_voidTransmiter(Data) ;
	LCD_EnableICPulse ()  ;
	LCD_voidEnable_4L() ;
	
	SPI_voidTransmiter(Copy_u8Command) ;
	LCD_EnableICPulse ()  ;
	LCD_voidEnable_4L() ;	
}


void LCD_voidClearIC_4L ()
{
	DIO_voidSetPinValue(PORTA_ID,RS,PIN_LOW);
	SPI_voidTransmiter(CLR_LCD_H);
	LCD_EnableICPulse ()  ;
	LCD_voidEnable_4L() ;
	
	DIO_voidSetPinValue(PORTA_ID,RS,PIN_LOW);
	SPI_voidTransmiter(CLR_LCD_L);
	LCD_EnableICPulse ()  ;
	LCD_voidEnable_4L() ;
}