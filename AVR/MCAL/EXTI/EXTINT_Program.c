
#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "EXTINT_Interface.h"
#include "EXTINT_Config.h"
#include "EXTINT_Private.h"

// Global pointer to function to can use it inside the ISR
void (*GPTF_EXT0)(void) ;
void (*GPTF_EXT1)(void) ;
void (*GPTF_EXT2)(void) ;


/* Enable global Interrupt */


void EXTINT_voidGloblaIniazlize()
{
	Set_bit(S_REG,I);                                   
}

void EXTINT_voidGloblaDisable()
{
	Clear_bit(S_REG,I);
}



void EXTINT_voidIntIialize(u8 Copy_u8IntNum)
{

	switch(Copy_u8IntNum)
	{
	case (EINT0):
	Set_bit(GICR_REG ,INT0);
	break ;

	case(EINT1):
	Set_bit(GICR_REG ,INT1);
	break;

	case(EINT2):
	Set_bit(GICR_REG ,INT2);
	break;
	}
}



void EXTINT_voidEnable(u8 Copy_u8IntNum,u8 Copy_u8SenseMode)
{
	

if (Copy_u8IntNum==EINT0)
{
		switch(Copy_u8SenseMode)
			{
				case (RAISING):                                                      
				Set_bit(MCUCR_REG ,ISC00);
				Set_bit(MCUCR_REG ,ISC01);
				break ;
				
				case(FAILING):                                                       
				Clear_bit(MCUCR_REG ,ISC00);
				Set_bit(MCUCR_REG ,ISC01);
				break;
				
				case(LOWLEVEL):                                                        
				Clear_bit(MCUCR_REG ,ISC00);
				Clear_bit(MCUCR_REG ,ISC01);
				break;
				
				case(ONCHANGE):
				Set_bit(MCUCR_REG ,ISC00);
				Clear_bit(MCUCR_REG ,ISC01);
				break;

			}
			
}


else if (Copy_u8IntNum==EINT1)

{
	switch(Copy_u8SenseMode)
		{
			case (RAISING):                                                      
					Set_bit(MCUCR_REG ,ISC10);
					Set_bit(MCUCR_REG ,ISC11);
					break ;
					
			case(FAILING):                                                       
				   Clear_bit(MCUCR_REG,ISC10);
				   Set_bit(MCUCR_REG,ISC11);
				   break;
				   
			case(LOWLEVEL):                                                        
					Clear_bit(MCUCR_REG ,ISC10);
					Clear_bit(MCUCR_REG ,ISC11);
					break;
					
			case(ONCHANGE):
					Set_bit(MCUCR_REG ,ISC10);
					Clear_bit(MCUCR_REG ,ISC11);
					break;
					
		}
}



else if (Copy_u8IntNum==EINT2)
{
	switch(Copy_u8SenseMode)
		{
	case (RAISING):                                                      
			Set_bit(MCUCSR_REG ,ISC2);
	        break ;
	case(FAILING):                                                       
		   Clear_bit(MCUCSR_REG ,ISC2);
		   break;

		}

}


}


void EXTINT_voidDisable(u8 Copy_u8IntNum)
{
	
	switch (Copy_u8IntNum)
	{
		
		
		case EINT0 :Clear_bit(GICR_REG ,INT0); break ;
		case EINT1 :Clear_bit(GICR_REG ,INT1); break ; 
		case EINT2 :Clear_bit(GICR_REG ,INT2); break ;  
		
	}
}








void EXTINT0_SetCallBack(void(*ptr)(void))
{

	GPTF_EXT0=ptr;
}

void EXTINT1_SetCallBack(void(*ptr)(void))
{

	GPTF_EXT1=ptr;
}

void EXTINT2_SetCallBack(void(*ptr)(void))
{

	GPTF_EXT2=ptr;
}




void __vector_1()__attribute__((signal));
void __vector_1()
{
	
	if (GPTF_EXT0!='\0')
	{
		GPTF_EXT0();
	}

}



void __vector_2()__attribute__((signal));
void __vector_2()
{
	if (GPTF_EXT1!='\0')
	{
	GPTF_EXT1(); 
	}
}



void __vector_3()__attribute__((signal));
void __vector_3()
{
	if (GPTF_EXT2!='\0')
	{
	GPTF_EXT2();
	}
}




