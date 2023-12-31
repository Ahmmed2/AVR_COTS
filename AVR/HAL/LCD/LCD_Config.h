#ifndef  _LED_CONFIG_H
#define  _LED_CONFIG_H


/*LCD Type */
#define LCD_TYPE	Four_BIT
#define Four_BIT		0 
#define Eight_BIT		1 

/* Data and Control Port */ 
#define CONTROL_PORT PORTA_ID
#define DATA_PORT    PORTB_ID

/* Control Pins */
#define RS PIN3_ID
#define EN PIN2_ID

/*Data Pins */ 
#define D7 PIN4_ID
#define D6 PIN2_ID
#define D5 PIN1_ID
#define D4 PIN0_ID

/* Lines */
#define LINE1  1
#define LINE2  2 
#define LINE3  3
#define LINE4  4 

/* OFFSET */
#define OFFSET0		 0
#define OFFSET1		 1
#define OFFSET2		 2
#define OFFSET3		 3
#define OFFSET4		 4
#define OFFSET5		 5
#define OFFSET6		 6
#define OFFSET7		 7
#define OFFSET8		 8
#define OFFSET9		 9
#define OFFSET10	 10
#define OFFSET11	 11
#define OFFSET12	 12
#define OFFSET13	 13
#define OFFSET14	 14
#define OFFSET15	 15
#define OFFSET16	 16
#define OFFSET17	 17
#define OFFSET18	 18
#define OFFSET19	 19
#define OFFSET20	 20


/* Shifting */ 
#define RIGHT									0
#define LEFT									1
#define DISPLAY_LEFT							2
#define DISPLAY_RIGHT							3


#endif 