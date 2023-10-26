#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "DIO_Interface.h"
#include "DIO_Config.h"

#include "KeyPad_Interface.h"
#include "KeyPad_Config.h"
#include "LCD_INTERFACE.h"
#include "LCD_Config.h"




/* Key Pad array  */
u8 sw_val[4][4]={{7,8,9,'/'},
				{4,5,6,'*'},
				{1,2,3,'-'},
				{10,0,'=','+'}};

////////////////////////////////////////////////////////


/* Pins Connected */

//Port D -->  Col
u8 Col_Arr[4] = {PIN7_ID,PIN6_ID,PIN4_ID,PIN3_ID};
//Port C  --> Rows
u8 Row_Arr[4] = {PIN5_ID,PIN4_ID,PIN3_ID,PIN2_ID};

////////////////////////////////////////////////////////


/* Initialization */


void KeyPad_voidInit()
{
	for (u8 i = 0 ; i< 4 ; i++)
	{
		/* Column */
		DIO_voidSetPinDirection(COLUMN_PORT,Col_Arr[i],PIN_INPUT_ID);
		/* Row */
		DIO_voidSetPinDirection(ROW_PORT,Row_Arr[i],PIN_OUTPUT_ID);
		DIO_voidSetPinValue(ROW_PORT,Row_Arr[i],PIN_HIGH );
		
	}
}

u8 KeyPad_u8GetPressedKey()
{
	KeyPad_voidInit() ;
	/* store the value of switch */
	u8 col ,row,check_press=1 ;
	
	/* If The Value Changed then there is switch pressed  */
	u8 val =0xff;
	

	for (row=row_start;row<row_end;row++)
	{
		
		/* Activate Row */
		DIO_voidSetPinValue(ROW_PORT,Row_Arr[row],PIN_LOW);

		for (col=col_start;col<col_end;col++)
		{
			/*  Which Switch is Pressed in Column */
			check_press=DIO_voidgetPinValue(COLUMN_PORT,Col_Arr[col]);
			
			//Switch pressed
			if (check_press==0)
			{
				val=sw_val[row][col];
				check_press=DIO_voidgetPinValue(COLUMN_PORT,Col_Arr[col]);
				
				while (!check_press)
				{
					check_press=DIO_voidgetPinValue(COLUMN_PORT,Col_Arr[col]);
				}
				_delay_ms(250);
				return val;
			}
		}
		// return row again to its initial State
		DIO_voidSetPinValue(ROW_PORT,Row_Arr[row] ,PIN_HIGH);
	}

	return val;
}



void KeyPad_voidCalculator()
{
	

	/* Variable Initialization */
	s32 Local_u32Result = 0   ;
	s32 Local_u32Num1 = 0 , Local_u32Num2 = 0   ;
	u8 Local_u8Operator , Local_u8Count = 0 , Local_u8keypad_press ;
	u8 Local_u8Num1Count = 0 , Local_u8Num2Count = 0 ;
	u8 Local_u8Index = 0 ;
	u8 Local_u8PressedKeys[20] = {0} ;
	u8 Local_u8Invalid[20]="Invalid Operation" ;
	u8 Local_u8Flag = 0;
	
	/* Clear LCD at the Beginning */
	LCD_voidClear() ;
	_delay_ms(100);
	
	while (Local_u8Flag == 0)
	{
		
		 
		Local_u8keypad_press = KeyPad_u8GetPressedKey();
		
		/* Check if Key is pressed and it is Number not operator and make sure that is the first Number */
		if ( (Local_u8keypad_press != 0xFF) && (Local_u8keypad_press >= 0) && (Local_u8keypad_press < 10) && (Local_u8Count==0) )
		{
			Local_u8PressedKeys[Local_u8Index] = Local_u8keypad_press ;
			LCD_voidDisplayNumber(Local_u8PressedKeys[Local_u8Index]);
			Local_u8Num1Count++ ;
			Local_u8Index++ ;
		}
		
		/* Determine which operator is pressed */
		else if (Local_u8keypad_press==MULTIPLY || Local_u8keypad_press==PLUS || Local_u8keypad_press==MINUS || Local_u8keypad_press==DIVISION )
		{
			Local_u8Operator = Local_u8keypad_press ;
			Local_u8Count++ ;
			LCD_voidSendDATA_4L(Local_u8keypad_press);
		}
		
		/* Check if Key is pressed and it is Number not operator and make sure that is the Second Number */
		else if ( (Local_u8keypad_press != 0xFF) && (Local_u8keypad_press >=0) && (Local_u8keypad_press < 10) && (Local_u8Count==1) )
		{
			Local_u8PressedKeys[Local_u8Index] = Local_u8keypad_press ;
			LCD_voidDisplayNumber(Local_u8PressedKeys[Local_u8Index]);
			Local_u8Num2Count++ ;
			Local_u8Index++ ;
		}
		
		/* Start to Evaluate the result when Equal is Pressed */
		else if (Local_u8keypad_press==EQUAL)
		{
			u8 Local_u8LoopCounter = 0 ;
			u32 Local_u32Temp = 0 ;
			u32 Local_u32Flag = 1 ;
			
			/* Determine  Number of digits of the first Number */
			for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter < Local_u8Num1Count-1 ; Local_u8LoopCounter++  )
			{
				Local_u32Flag *= 10  ;
			}
			
			
			/* Evaluate First Number */
			for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter < Local_u8Num1Count ; Local_u8LoopCounter++ )
			{
				Local_u32Temp = Local_u32Temp + (Local_u8PressedKeys[Local_u8LoopCounter] * Local_u32Flag)  ;
				Local_u32Flag /= 10 ;
			}
			
			
			Local_u32Num1 = Local_u32Temp ;
			
			
			
			
			/* Reinitialize the Variables again to its Initial Values */
			Local_u32Flag = 1 ;
			Local_u32Temp = 0 ;
			
			/* Determine The Number of digit of the Second Number */
			for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter <Local_u8Num2Count-1 ; Local_u8LoopCounter++  )
			{
				Local_u32Flag = 10 * Local_u32Flag ;
			}
			
			/* Evaluate Second Number */
			for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter <Local_u8Num2Count ; Local_u8LoopCounter++ )
			{
				Local_u32Temp = Local_u32Temp + (Local_u8PressedKeys[Local_u8LoopCounter+Local_u8Num1Count] * Local_u32Flag)  ;
				Local_u32Flag /= 10 ;
			}
			
			Local_u32Num2 = Local_u32Temp ;
				
			/*Clear LCD in order to print Result */
			LCD_voidClear() ;
			_delay_ms(200);
			
			/* Perform  Operation */
			switch (Local_u8Operator)
			{
				case PLUS     :		Local_u32Result = Local_u32Num1 + Local_u32Num2	; 	 break ;
				case MINUS	  :		Local_u32Result = Local_u32Num1 - Local_u32Num2	; 	 break ;
				case MULTIPLY :		Local_u32Result = Local_u32Num1 * Local_u32Num2	; 	 break ;
				case DIVISION :		Local_u32Result = Local_u32Num1 / Local_u32Num2	; 	 break ;
				default		  :		LCD_voidWriteSting(Local_u8Invalid,LINE1)	 ;				 break ;
			}
			
			/* Print the Result */ 
			if (Local_u32Result<0)
			{
				LCD_voidSendDATA_4L('-');
				LCD_voidDisplayNumber(abs(Local_u32Result));
			}
			else LCD_voidDisplayNumber(abs(Local_u32Result));
		
		}
		
		/*To Shut down the Calculator*/
		else if (Local_u8keypad_press == TERMINATE)
		{
			LCD_voidClear();
			 Local_u8Flag = 1 ;
		}
		
	}
	
	
	
}

