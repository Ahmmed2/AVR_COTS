#ifndef  _TR_CONFIG_
#define  _TR_CONFIG_

/* Timer0 */ 


#define TCNT0   *((volatile u8*) 0x52)

#define TCCR0	*((volatile u8*) 0x53)
/* Bits */ 
#define CS00		   0
#define CS01		   1
#define CS02		   2
#define WGM01		   3
#define COM00		   4
#define COM01		   5
#define	WGM00		   6
#define FOC0		   7
////////////////////

#define TIFR	*((volatile u8*) 0x58)
/* Bits */
#define TOV1		2
#define OCF1B		3
#define OCF1A		4
#define ICF1		5
#define TOV2		6
#define OCF2		7
////////////////////

#define TIMSK	*((volatile u8*) 0x59)
/* Bits */ 
#define TOIE0			   0
#define OCIE0			   1
#define TOIE1              2
#define OCIE1B             3
#define OCIE1A             4
#define TICIE1             5
////////////////////

#define OCR0	*((volatile u8*) 0x5C)


 ////////////////////////////////////////////////////////////

/* Timer1 */ 

#define TCCR1A	  *((volatile u16*) 0x4F)
/* Bits */ 
#define WGM10              0
#define WGM11              1
#define FOC1B              2
#define FOC1A              3
#define COM1B0             4
#define COM1B1             5
#define COM1A0             6
#define COM1A1             7


#define TCCR1B	  *((volatile u16*) 0x4E)
/* Bits */ 
#define CS10               0
#define CS11               1
#define CS12               2
#define WGM12              3
#define WGM13              4
#define ICES1              6
#define ICNC1              7


#define ICR1H	  *((volatile u8*) 0x47)
#define ICR1L	  *((volatile u8*) 0x46)
#define ICR1	  *((volatile u16*) 0x46)
#define OCR1AH	  *((volatile u8*) 0x4B)
#define OCR1AL	  *((volatile u8*) 0x4A)
#define OCR1A	  *((volatile u16*) 0x4A)
#define TCNT1	  (*((volatile u16*) 0x4C))
#define OCR1B     (*((volatile u16*) 0x48))






////////////////////////////////////////////////////////////////

/* Timer 2 */ 

#define TIMSK	*((volatile u8*) 0x59)
/* Bits */
#define TOIE2		6
#define OCIE2		7
////////////////////

#define TIFR	*((volatile u8*) 0x58)
/* Bits */
#define TOV2		6
#define OCF2		7
/////////////////////


#define TCCR2 *((volatile u8*) 0x45)
/* Bits */ 
#define  CS20		 0
#define  CS21		 1
#define  CS22		 2
#define  WGM21		 3
#define  COM20		 4
#define  COM21		 5
#define	 WGM20		 6
#define  FOC2		 7
////////////////////

#define TCNT2 *((volatile u8*) 0x44) 
#define OCR2  *((volatile u8*) 0x43)













#endif 
