/*
 * Seven_Segment_Config.h
 *
 * Created: 9/15/2023 9:09:03 AM
 *  Author: Ahmed
 */ 


#ifndef SEVEN_SEGMENT_CONFIG_H_
#define SEVEN_SEGMENT_CONFIG_H_

/* Seven Segment Numbers */ 
#define FIRST_7_SEG				1    
#define	SECOND_7_SEG			2
#define	THIRD_7_SEG				3
#define	FOURTH_7_SEG			4


/* To choose which 7-Segment is working */ 

/* Port */ 
#define FIRST_7_SEG_PORT		PORTB_ID
#define SECOND_7_SEG_PORT		PORTB_ID
#define THIRD_7_SEG_PORT		PORTA_ID
#define FOURTH_7_SEG_PORT		PORTA_ID

/* Pin */ 
#define FIRST_7_SEG_PIN			PIN6_ID
#define SECOND_7_SEG_PIN		PIN5_ID
#define THIRD_7_SEG_PIN			PIN2_ID
#define FOURTH_7_SEG_PIN		PIN3_ID



/* BCD */

/* Port */
#define SEVEN_SEGMENT_PORT		PORTB_ID	
/* Pin */ 
#define SEVEN_SEGMENT_PIN1		PIN0_ID
#define SEVEN_SEGMENT_PIN2		PIN1_ID
#define SEVEN_SEGMENT_PIN3		PIN2_ID
#define SEVEN_SEGMENT_PIN4		PIN4_ID



#define ZERO				0b0000
#define ONE					0b0001
#define TWO					0b0010
#define THREE				0b0011
#define FOUR				0b0100
#define FIVE				0b0101
#define SIX					0b0110
#define SEVEN				0b0111
#define EIGHT				0b1000
#define NINE				0b1001
#define TEN					0b0000
#define TWELVE				0b0000
#define THIRTEEN			0b0000


#endif /* SEVEN_SEGMENT_CONFIG_H_ */

