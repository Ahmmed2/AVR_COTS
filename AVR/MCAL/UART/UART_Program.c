


#include "Std_Types.h"
#include "Macros.h"

#include "UART_Private.h"
#include "UART_Config.h"
#include "UART_Interface.h"

//RX Complete 
void (*UARTRXC_GPTR)(u8)	;
//Data Register Empty 
void (*UARTDRE_GPTR)(void)	;
//TX Complete 
void (*UARTTXC_GPTR)(void)	;


void UART_voidInialize()
{
	u8 Copy_u8Value = 0b00000000 ;
	
	//Register Enable
	Set_bit(Copy_u8Value,7);
	
									/* Mode */	
#if UART_MODE == UART_ASYNCHRONUS
	//ASynchronous
	Clear_bit(Copy_u8Value,6);
#elif UART_MODE == UART_SYNCHRONUS
	// Synchronous 
	Clear_bit(Copy_u8Value,6);
#endif 

									/* Parity */
#if PARITY_MODE == PARITY_DISABLED
	//No parity
	Clear_bit(Copy_u8Value,4);
	Clear_bit(Copy_u8Value,5);
#elif PARITY_MODE == PARITY_EVEN 
	//Even Parity
	Clear_bit(Copy_u8Value,4);
	Set_bit(Copy_u8Value,5);	 
#elif PARITY_MODE == PARITY_ODD
	//Odd Parity 
	Set_bit(Copy_u8Value,4);
	Set_bit(Copy_u8Value,5);
#endif 
									/* Stop-Bits */ 

#if STOP_MODE == SINGLE_STOP
	//Single Stop Bit 
	Clear_bit(Copy_u8Value,3);	
#elif STOP_MODE == DOUBLE_STOP
	//Double Stop Bit
	Set_bit(Copy_u8Value,3);
#endif 

									/* Character Size */ 
					
// The Third Bit is By default zero 								
	
#if  CHARACTER_MODE == FIVE_BIT
	Clear_bit(Copy_u8Value,1);
	Clear_bit(Copy_u8Value,2);
		
#elif CHARACTER_MODE == SIX_BIT
	Set_bit(Copy_u8Value,1);
	Clear_bit(Copy_u8Value,2);

#elif CHARACTER_MODE == SEVEN_BIT
	Clear_bit(Copy_u8Value,1);
	Set_bit(Copy_u8Value,2);
	
#elif CHARACTER_MODE == EIGHT_BIT
	Set_bit(Copy_u8Value,1);
	Set_bit(Copy_u8Value,2);
	
#elif CHARACTER_MODE == NINE_BIT
	Set_bit(Copy_u8Value,1) ;
	Set_bit(Copy_u8Value,2) ;	
	Set_bit(UCSRB,2) ; 
	
#endif 

	UCSRC_UBRRH=Copy_u8Value;
	
									/* BaudRate  */ 
									
	// To Adjust the Baud Rate 					
	//Clear_bit(UCSRC_UBRRH,7);
	
#if BAUD_MODE == BAUD_4800 
	UBRRL = 207 ;
#elif BAUD_MODE == BAUD_9600 
	UBRRL = 103 ; 
#elif BAUD_MODE == BAUD_14d4
	UBRRL = 68 ;
#elif BAUD_MODE == BAUD_19d2
	UBRRL = 51 ;
#elif BAUD_MODE == BAUD_28d8K
	UBRRL = 34 ;
#elif BAUD_MODE == BAUD_38d4K
	UBRRL = 25 ;
#elif BAUD_MODE == BAUD_57d6K
	UBRRL = 16 ;
#elif BAUD_MODE == BAUD_76d8K
	UBRRL = 12 ;
#elif BAUD_MODE == BAUD_115d2K
	UBRRL = 8 ;
#elif BAUD_MODE == BAUD_230d4K
	UBRRL = 3 ;
#elif BAUD_MODE == BAUD_250K
	UBRRL = 3 ;
#endif

#if POLARITY_MODE == TX_RISING_RX_FALLING 
	Clear_bit(UCSRC_UBRRH,0) ; 
#elif POLARITY_MODE == TX_FALLING_RX_RISING 
	Set_bit(UCSRC_UBRRH,0) ;
#endif 

	//Enable TX and RX
	Set_bit(UCSRB,3);
	Set_bit(UCSRB,4);
	
	
}


void UART_SendData(u8 Copy_u8Value)
{
#if CHECK_MODE == UART_POLLING 
	UDR=Copy_u8Value;
	while ((Get_bit(UCSRA,5))==0);


#elif CHECK_MODE == UART_INTERRUPT

	// TX Complete Interrupt Enable
	Set_bit(UCSRB,6) ;
	UDR=Copy_u8Value;
	
	// USART Data Register Empty Interrupt Enable
	//Set_bit(UCSRB,5) ;

#endif 	
	
}


u8 UART_ReceiveData()
{
#if CHECK_MODE == UART_POLLING 
	while ((Get_bit(UCSRA,7))==0);
	return UDR ;
	
#elif CHECK_MODE == UART_INTERRUPT
	//RX Complete Interrupt Enable
	Set_bit(UCSRB,7) ;
	
	
#endif 
}

void UART_voidSendString(u8 Copy_u8String[])
{
	u8 Local_u8Counter =  0 ;
	while (	Copy_u8String[Local_u8Counter] != '\0')
	{
		UART_SendData (Copy_u8String[Local_u8Counter]) ;
		Local_u8Counter ++ ;
		
	}
}

void UART_voidReceiveString(u8 Copy_u8String[])
{
	u8 Local_u8Counter =  0 ;
	while (	Copy_u8String[Local_u8Counter] != '\0')
	{
		Copy_u8String[Local_u8Counter] = UART_ReceiveData () ;
		Local_u8Counter ++ ;
		
	}
}


/////////////////////////////////////////////////////////////////

// RX Complete 
void __vector_13()__attribute__((signal));
void __vector_13()
{
	
	UARTRXC_GPTR (UDR) ;
}

// Data Register Empty 
void __vector_14()__attribute__((signal));
void __vector_14()
{
	
	UARTDRE_GPTR () ;
}

// TX Complete
void __vector_15()__attribute__((signal));
void __vector_15()
{
	UARTTXC_GPTR () ;	
}


void UARTRXC_SetCallBack(void(*ptr)(void))
{
	UARTRXC_GPTR=ptr;
}

void UARTDRE_SetCallBack(void(*ptr)(void))
{
	UARTDRE_GPTR=ptr;
}

void UARTTXC_SetCallBack(void(*ptr)(void))
{
	UARTTXC_GPTR=ptr;
}