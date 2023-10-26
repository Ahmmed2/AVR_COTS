#ifndef  UART_CONFIG
#define  UART_CONFIG

//Mode		
#define UART_SYNCHRONUS				0
#define UART_ASYNCHRONUS			1

//Parity 
#define PARITY_DISABLED				0
#define PARITY_EVEN					2
#define PARITY_ODD					3

//Stop bits 
#define SINGLE_STOP					0
#define DOUBLE_STOP					1

//Character Size 
#define FIVE_BIT					0 
#define SIX_BIT						1
#define SEVEN_BIT					2
#define EIGHT_BIT					3
#define NINE_BIT					4 

//Baud Rate 
#define BAUD_4800					0
#define BAUD_9600					1
#define BAUD_14d4					2
#define BAUD_19d2					3
#define BAUD_28d8K					4
#define BAUD_38d4K					5
#define BAUD_57d6K					6
#define BAUD_76d8K					7
#define BAUD_115d2K					8
#define BAUD_230d4K					9
#define BAUD_250K					10

//Clock Polarity 
#define TX_RISING_RX_FALLING		0	
#define TX_FALLING_RX_RISING		1

//Check Mode 
#define UART_POLLING				0
#define UART_INTERRUPT				1

#endif