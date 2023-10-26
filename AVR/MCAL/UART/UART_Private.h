#ifndef  UART_PRIVATE
#define  UART_PRIVATE

#define UCSRB			*((volatile u8*) 0x2A)
#define UCSRC_UBRRH		*((volatile u8*) 0x40)
#define UBRRL			*((volatile u8*) 0x29)
/* Used to TX and Rx Data */ 
#define UDR				*((volatile u8*) 0x2C)
/* Interrupts Enable */
#define UCSRA			*((volatile u8*) 0x2B)


#endif