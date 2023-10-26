

#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"


#include "DIO_Private.h"
#include "DIO_Interface.h"
#include "DIO_Config.h"


u8 Pins_States[32]={PA0_CFG,PA1_CFG,PA2_CFG,PA3_CFG,PA4_CFG,PA5_CFG,PA6_CFG,PA7_CFG,PB0_CFG,PB1_CFG,PB2_CFG,
					PB3_CFG,PB4_CFG,PB5_CFG,PB6_CFG,PB7_CFG,PC0_CFG,PC1_CFG,PC2_CFG,PC3_CFG,PC4_CFG,PC5_CFG,
					PC6_CFG,PC7_CFG,PD0_CFG,PD1_CFG,PD2_CFG,PD3_CFG,PD4_CFG,PD5_CFG,PD6_CFG,PD7_CFG};



void DIO_voidInitialize_CFG()
{
	
	
	DIO_voidSetPort_CFG();
	
}






void DIO_voidSetPort_CFG()
{
	u8 flag = 0 ;
	for (int i = 0 ;i<32 ; i++ )
	{
		
		
		if (i>=0 && i<8)
		{
			
			if (Pins_States[i]==INPUT_PP)
			{
				DIO_voidSetPinDirection(PORTA_ID,i,PIN_INPUT_ID);
				DIO_voidSetPinValue(PORTA_ID,i,PIN_HIGH);
			}
			else if (Pins_States[i]==OUTPUT_HIGH)
			{
				DIO_voidSetPinDirection(PORTA_ID,i,PIN_OUTPUT_ID);
				DIO_voidSetPinValue(PORTA_ID,i,PIN_HIGH);
			}
			else if (Pins_States[i]==OUTPUT_LOW)
			{
				DIO_voidSetPinDirection(PORTA_ID,i,PIN_OUTPUT_ID);
				DIO_voidSetPinValue(PORTA_ID,i,PIN_LOW);
			}
		}
		
		else 
		{
			if (i>=8 && i<16)       flag=1 ;
			else if (i>=16 && i<24) flag=2 ;
			else if (i>=24 && i<32) flag=3 ;
			
					if (Pins_States[i]==INPUT_PP)
					{
						if (flag==1){
							DIO_voidSetPinDirection(PORTB_ID,i-8*flag,PIN_INPUT_ID);
							DIO_voidSetPinValue(PORTB_ID,i-8*flag,PIN_HIGH);}
						else if (flag==2) {
							DIO_voidSetPinDirection(PORTC_ID,i-8*flag,PIN_INPUT_ID);
							DIO_voidSetPinValue(PORTC_ID,i-8*flag,PIN_HIGH);}
						else {
							DIO_voidSetPinDirection(PORTD_ID,i-8*flag,PIN_INPUT_ID);
							DIO_voidSetPinValue(PORTD_ID,i-8*flag,PIN_HIGH);}
					}
					else if (Pins_States[i]==OUTPUT_HIGH)
					{
							if (flag==1){
								DIO_voidSetPinDirection(PORTB_ID,i-8*flag,PIN_OUTPUT_ID);
							DIO_voidSetPinValue(PORTB_ID,i-8*flag,PIN_HIGH);}
							else if (flag==2) {
								DIO_voidSetPinDirection(PORTC_ID,i-8*flag,PIN_OUTPUT_ID);
							DIO_voidSetPinValue(PORTC_ID,i-8*flag,PIN_HIGH);}
							else {
								DIO_voidSetPinDirection(PORTD_ID,i-8*flag,PIN_OUTPUT_ID);
							DIO_voidSetPinValue(PORTD_ID,i-8*flag,PIN_HIGH);}
					}
					else if (Pins_States[i]==OUTPUT_LOW)
					{
								if (flag==1){
									DIO_voidSetPinDirection(PORTB_ID,i-8*flag,PIN_OUTPUT_ID);
								DIO_voidSetPinValue(PORTB_ID,i-8*flag,PIN_LOW);}
								else if (flag==2) {
									DIO_voidSetPinDirection(PORTC_ID,i-8*flag,PIN_OUTPUT_ID);
								DIO_voidSetPinValue(PORTC_ID,i-8*flag,PIN_LOW);}
								else {
									DIO_voidSetPinDirection(PORTD_ID,i-8*flag,PIN_OUTPUT_ID);
								DIO_voidSetPinValue(PORTD_ID,i-8*flag,PIN_LOW);}
					
						
					}
			
		}
	}
}


void DIO_voidSetPinValue_From_Single_Pin(u8 Copy_u8PinID,u8 Copy_u8PinValue)
{
       u8 value = Copy_u8PinID / 8 ;
	   if (value == 0)
	   {
		   DIO_voidSetPinValue(PORTA_ID,Copy_u8PinID,Copy_u8PinValue);
		   
	   }
	   else if (value == 1)
	   {
		   
		   DIO_voidSetPinValue(PORTB_ID,Copy_u8PinID-8,Copy_u8PinValue);
	   }
	  else if (value==2)
	  {
		  DIO_voidSetPinValue(PORTC_ID,Copy_u8PinID-16,Copy_u8PinValue);
	  }
	  else 	DIO_voidSetPinValue(PORTD_ID,Copy_u8PinID-24,Copy_u8PinValue);
	  
	/*    if (Copy_u8PinID>=0 && Copy_u8PinID<8)
		{
			DIO_voidSetPinValue(PORTA_ID,Copy_u8PinID,Copy_u8PinValue);
		}
		else if (Copy_u8PinID>=8 && Copy_u8PinID<16)  
		{
			DIO_voidSetPinValue(PORTB_ID,Copy_u8PinID-8,Copy_u8PinValue);
		}
		else if (Copy_u8PinID>=16 && Copy_u8PinID<24)  
		{
			DIO_voidSetPinValue(PORTC_ID,Copy_u8PinID-16,Copy_u8PinValue);
		}
		else if (Copy_u8PinID>=24 && Copy_u8PinID<32)
		{
			DIO_voidSetPinValue(PORTD_ID,Copy_u8PinID-24,Copy_u8PinValue);
			
		}*/
}

void DIO_voidSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinDir)
{
	if (Copy_u8PinDir==PIN_OUTPUT_ID)
	{
		switch (Copy_u8PortID)
		{
			
			case (PORTA_ID):        Set_bit(DDRA_REG,Copy_u8PinID);        
			break ;
			case (PORTB_ID):        Set_bit(DDRB_REG,Copy_u8PinID);        
			break ;
			case (PORTC_ID):        Set_bit(DDRC_REG,Copy_u8PinID);        
			break ;
			case (PORTD_ID):        Set_bit(DDRD_REG,Copy_u8PinID);        
			break ;
			
			
		}
		
	}
	else if (Copy_u8PinDir==PIN_INPUT_ID)
	{
		switch (Copy_u8PortID)
		{
			
			case (PORTA_ID):        Clear_bit(DDRA_REG,Copy_u8PinID);        //Port A
			break ;
			case (PORTB_ID):        Clear_bit(DDRB_REG,Copy_u8PinID);        //Port B
			break ;
			case (PORTC_ID):        Clear_bit(DDRC_REG,Copy_u8PinID);       //Port C
			break ;
			case (PORTD_ID):        Clear_bit(DDRD_REG,Copy_u8PinID);       //Port D
			break ;
			
			
		}
	}
	
}


void DIO_voidSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinValue)
{
	
	if (Copy_u8PinValue==PIN_HIGH)
	{
		switch (Copy_u8PortID)
		{
			
			case (PORTA_ID):        Set_bit(PORTA_REG,Copy_u8PinID);        // Port A
			break ;
			case (PORTB_ID):        Set_bit(PORTB_REG,Copy_u8PinID);        //Port B
			break ;
			case (PORTC_ID):        Set_bit(PORTC_REG,Copy_u8PinID);        //Port C
			break ;
			case (PORTD_ID):        Set_bit(PORTD_REG,Copy_u8PinID);        //Port D
			break ;
			
			
		}
		
	}
	
	else if (Copy_u8PinValue==PIN_LOW)
	{
		switch (Copy_u8PortID)
		{
			
			case (PORTA_ID):        Clear_bit(PORTA_REG,Copy_u8PinID);
			break ;
			case (PORTB_ID):        Clear_bit(PORTB_REG,Copy_u8PinID);
			break ;
			case (PORTC_ID):        Clear_bit(PORTC_REG,Copy_u8PinID);
			break ;
			case (PORTD_ID):        Clear_bit(PORTD_REG,Copy_u8PinID);
			break ;
			
			
		}
	}
	
	
}

void DIO_voidSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortDir)
{
	switch(Copy_u8PortID)
	{
		case PORTA_ID: DDRA_REG= Copy_u8PortDir; break;
		case PORTB_ID: DDRB_REG= Copy_u8PortDir; break;
		case PORTC_ID: DDRC_REG= Copy_u8PortDir; break;
		case PORTD_ID: DDRD_REG= Copy_u8PortDir; break;
	}
}


void DIO_voidSetPortValue(u8 Copy_u8PortID, u8 Copy_u8PortValue)
{
	switch(Copy_u8PortID)
	{
		case PORTA_ID: PORTA_REG= Copy_u8PortValue; break;
		case PORTB_ID: PORTB_REG= Copy_u8PortValue; break;
		case PORTC_ID: PORTC_REG= Copy_u8PortValue; break;
		case PORTD_ID: PORTD_REG= Copy_u8PortValue; break;
	}

}









u8 DIO_voidgetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID)
{


	u8 value ;


	switch(Copy_u8PortID)
	{


		case (PORTA_ID) :
	    value=Get_bit(PINA_REG,Copy_u8PinID);
		break ;

		case (PORTB_ID) :
		value=Get_bit(PINB_REG,Copy_u8PinID);
		break ;


		case (PORTC_ID) :
		value=Get_bit(PINC_REG,Copy_u8PinID);
		break ;

		case (PORTD_ID) :
		value=Get_bit(PIND_REG,Copy_u8PinID);
		break ;

	}
	return value ;

}


void DIO_voidTogglePinValue(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
	switch(Copy_u8PortID)
	{


		case (PORTA_ID) :Toggle_bit(PORTA_REG,Copy_u8PinID);
		
		break ;

		case (PORTB_ID) :Toggle_bit(PORTB_REG,Copy_u8PinID);
		
		break ;


		case (PORTC_ID) :Toggle_bit(PORTC_REG,Copy_u8PinID);
		
		break ;

		case (PORTD_ID) :Toggle_bit(PORTD_REG,Copy_u8PinID);
		
		break ;

	}
	
	
}


