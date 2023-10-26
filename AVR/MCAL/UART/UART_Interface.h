#ifndef  UART_INTERFACE
#define  UART_INTERFACE


#define UART_MODE			UART_ASYNCHRONUS
#define PARITY_MODE			PARITY_DISABLED
#define STOP_MODE			SINGLE_STOP
#define CHARACTER_MODE		EIGHT_BIT
#define BAUD_MODE			BAUD_9600
#define POLARITY_MODE		TX_RISING_RX_FALLING 
#define CHECK_MODE			UART_POLLING


void UART_voidInialize();
void UART_SendData(u8 Copy_u8Value);
u8 UART_ReceiveData();
void UART_voidSendString(u8 Copy_u8String[]);
void UART_voidReceiveString(u8 Copy_u8String[]);



// Set Call Back 
void UARTRXC_SetCallBack(void(*ptr)(void))	;
void UARTDRE_SetCallBack(void(*ptr)(void)) ;
void UARTTXC_SetCallBack(void(*ptr)(void)) ;

#endif