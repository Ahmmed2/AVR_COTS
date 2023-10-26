/*
 * StackBasedCalculator_Program.c
 *
 * Created: 9/21/2023 4:26:56 PM
 *  Author: Ahmed
 */ 


#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Std_Types.h"
#include "Macros.h"

#include "StackBasedCalculator_Interface.h"

#include "DIO_Config.h"
#include "DIO_Interface.h"
#include "LCD_Config.h"
#include "LCD_INTERFACE.h"
#include "KEYPAD_Config.h"
#include "KEYPAD_Interface.h"





/////////////////////////

#define MAX          20
#define MAX_ELEMENTS 20

/////////////////////////
/* Data Type Definition */
/* Second Stack */
struct Node
{
	u8 Data_SecondStack;
	struct Node *Link_SecondStack ;
};

struct Node *Top_SecondSack=NULL ;

//////////////////
/* Global Variables */
s8 Top_FirstStack = -1;
u8 Stack_Array[MAX] ;
char str[MAX],stack[MAX];
int top=-1;
char c[20];



/* First Stack */
s8 isEmpty_FirstStack()
{
	return Top_FirstStack == -1;
	
}
u8 isFull_FirstStack()
{
	return Top_FirstStack == MAX - 1;
}
u8 Peek_FirstStack()
{
	return Stack_Array[Top_FirstStack];
}
s8 POP_FirstStack()
{
	if(isEmpty_FirstStack())
	return -1;
	
	u8 ch = Stack_Array[Top_FirstStack];
	Top_FirstStack--;
	return(ch) ;
}
void Push_FirstStack(u8 oper)
{
	if(isFull_FirstStack())
	{
		
	}

	
	else
	{
		Top_FirstStack++;
		Stack_Array[Top_FirstStack] = oper;
	}
}
int checkIfOperand(u8 Number)
{
	return (Number >= '0' && Number <= '9') ;
}
s8 precedence(u8 Operator)
{
	u8 Local_Return = 0 ;
	switch (Operator)
	{
		case '+':
		case '-':
		Local_Return = 1;   break;
		
		case '*':
		case '/':
		Local_Return = 2;   break;
		
		case '^':
		Local_Return = 3;  break;

		default : Local_Return = -1; break;
	}
	return  Local_Return ;
	
}

s8 covertInfixToPostfix( u8 *Expression)
{
	u8 Local_u8Counter ;
	s8 Local_u8Index  ;
	s8 Local_u8LoopCounter = 0 ;
    u8 Operator_Array[10] ; 
	
	for (Local_u8Counter = 0, Local_u8Index = -1 ; Expression[Local_u8Counter] ; ++Local_u8Counter)
	{
		if (checkIfOperand(Expression[Local_u8Counter]))
		Expression[++Local_u8Index] = Expression[Local_u8Counter];
		
		else if (Expression[Local_u8Counter] == '(')
		Push_FirstStack(Expression[Local_u8Counter]);
		
		else if (Expression[Local_u8Counter] == ')')
		{
			while (!isEmpty_FirstStack() && Peek_FirstStack() != '(')
			Expression[++Local_u8Index] = POP_FirstStack();
			if (!isEmpty_FirstStack() && Peek_FirstStack() != '(')
			return -1;
			else
			POP_FirstStack();
		}
		else
		{
			while (!isEmpty_FirstStack() && precedence(Expression[Local_u8Counter]) <= precedence(Peek_FirstStack()))
			Expression[++Local_u8Index] = POP_FirstStack();
			
			Push_FirstStack(Expression[Local_u8Counter]);
		}
	}
	
	
	
	while (!isEmpty_FirstStack())
	Expression[++Local_u8Index] = POP_FirstStack();
	
	Expression[++Local_u8Index] = '\0';
	
  for (int i = 0 ; i<Local_u8Index ; i++ )
  {
   str[i] = Expression[i];
  }
  
	pre_post() ;


	


}

/* Second Stack  */
void Push_SecondStack(u8 data )
{
	struct Node *NewNode = NULL ;
	NewNode = malloc(sizeof(struct Node));

	if (NewNode==NULL) //to check if there are Space or not
	{
	
		exit(1);
	}
	NewNode->Data_SecondStack = data ;
	NewNode->Link_SecondStack = NULL ;
	NewNode->Link_SecondStack = Top_SecondSack ;
	Top_SecondSack=NewNode ;

}

u8 POP_SecondStack()
{
	if (Top_SecondSack==NULL)
	{

		exit(1);
	}

	struct Node *Temp ;
	Temp = Top_SecondSack ;
	u8 value=Top_SecondSack->Data_SecondStack ;
	Top_SecondSack=Top_SecondSack->Link_SecondStack ;
	free(Temp);
	return value ;

}

void Calc_Result (u8 arr[])
{
	u8 Local_u8Result =0 ;
	u8 Input_Length;
	u8 Local_u8Number ;
	u8 Local_u8Value1,Local_u8Value2 ;
	u8 Local_u8LoopCounter = 0 ;

	Input_Length = strlen(arr) ;



	for (Local_u8LoopCounter = 0 ; Local_u8LoopCounter<Input_Length ; Local_u8LoopCounter++)
	{
		if (arr[Local_u8LoopCounter]>=0 && arr[Local_u8LoopCounter]<=9)
		{
			
			Local_u8Number=arr[Local_u8LoopCounter] ;
			Push_SecondStack(Local_u8Number);
		}
		else if (arr[Local_u8LoopCounter]=='*')
		{
			Local_u8Value1=POP_SecondStack() ;
			Local_u8Value2=POP_SecondStack() ;
			Local_u8Result=Local_u8Value2*Local_u8Value1 ;
			Push_SecondStack (Local_u8Result) ;
		}
		else if (arr[Local_u8LoopCounter]=='-')
		{
			Local_u8Value1=POP_SecondStack();
			Local_u8Value2=POP_SecondStack();
			Local_u8Result=Local_u8Value2-Local_u8Value1 ;
			Push_SecondStack(Local_u8Result);
		}
		else if (arr[Local_u8LoopCounter]=='+')
		{
			Local_u8Value1=POP_SecondStack();
			Local_u8Value2=POP_SecondStack();
			Local_u8Result=Local_u8Value2+Local_u8Value1 ;
			Push_SecondStack(Local_u8Result);
		}
		else if (arr[Local_u8LoopCounter]=='/')
		{
			Local_u8Value1=POP_SecondStack() ;
			Local_u8Value2=POP_SecondStack() ;
			
			if (Local_u8Value1==0)
			{

				exit(0) ;
			}
			else
			{
				Local_u8Result=Local_u8Value2/Local_u8Value1 ;
				Push_SecondStack(Local_u8Result);
			}
		}


		else if (arr[Local_u8LoopCounter]=='%')
		{
			Local_u8Value1=POP_SecondStack();
			Local_u8Value2=POP_SecondStack();
			if (Local_u8Value1==0)
			{

				exit(0) ;
			}
			else
			{
				Local_u8Result=Local_u8Value2%Local_u8Value1 ;
				Push_SecondStack(Local_u8Result);
			}
		}
	}

	if (Top_SecondSack->Link_SecondStack==NULL)
	{
		LCD_voidWriteSting("Result :" ,LINE2) ;
       LCD_voidDisplayNumber(Local_u8Result);
	}
	else
	{

		
	}

}



void StackBasedCalculator_voidShowInput ()
{
	
	
	/* Clear LCD at the Beginning */
	LCD_voidClear() ;
	_delay_ms(100);
	
	
	/* Variable Initialization */

	u8 Local_u8keypad_press ;
	u8 Local_u8Index = 0 ;
	u8 Local_u8PressedKeys[20] = {0} ;
	u8 Local_u8Flag = 0;

	
	while (Local_u8Flag == 0)
	{
		
		
		Local_u8keypad_press = KeyPad_u8GetPressedKey();
		
		/* Check if Key is pressed and it is Number not operator and make sure that is the first Number */
		if ( (Local_u8keypad_press != 0xFF) && (Local_u8keypad_press >= 0) && (Local_u8keypad_press < 10) )
		{
			Local_u8PressedKeys[Local_u8Index] = Local_u8keypad_press ;
			LCD_voidDisplayNumber(Local_u8PressedKeys[Local_u8Index]);
			Local_u8Index++ ;
		}
		
		/* Determine which operator is pressed */
		else if (Local_u8keypad_press==MULTIPLY || Local_u8keypad_press==PLUS || Local_u8keypad_press==MINUS || Local_u8keypad_press==DIVISION )
		{
			Local_u8PressedKeys[Local_u8Index] = Local_u8keypad_press ;
			Local_u8Index++ ;
			LCD_voidSendDATA_4L(Local_u8keypad_press);
		}
		else if (Local_u8keypad_press==EQUAL)
		{		
			LCD_GoToXY(LINE2,OFFSET0);
			Local_u8PressedKeys[Local_u8Index] = '\0' ;
			covertInfixToPostfix(Local_u8PressedKeys); 
			
		}
		
	
	}
}

void push(char c)
{
	stack[++top]=c;
}

char pop()
{
   return stack[top--];
}

void pre_post()
{
	int n,i,j=0; char c[20];
	char a,b,op; u8 Local_u8LoopCounter = 0;
	n=strlen(str);
	for(i=0;i<MAX;i++)
	stack[i]='\0';

	for(i=0;i<n;i++)
	{
		if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')
		{
			push(str[i]);
		}
		else
		{ c[j++]=str[i];
			while((top!=-1)&&(stack[top]=='@'))
			{
				a=pop(); c[j++]=pop();
			}
			push('@');
		}
	}
	c[j]='\0';
	
		LCD_voidWriteSting("Postfix:",LINE1) ;
		while (Local_u8LoopCounter <= j -1 )
		{
			if (c[Local_u8LoopCounter] >=0 && c[Local_u8LoopCounter] <=9 ) LCD_voidDisplayNumber(c[Local_u8LoopCounter]) ;
			else LCD_voidSendDATA_4L(c[Local_u8LoopCounter]) ;
			
			Local_u8LoopCounter ++ ;
		}
		LCD_GoToXY(LINE2,OFFSET0);
		Calc_Result (c)	;

}