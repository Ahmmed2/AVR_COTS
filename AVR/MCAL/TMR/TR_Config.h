

#ifndef  TR_CONFIG
#define  TR_CONFIG

#define TIMER_FREQ     16000000

/* Timers */ 
#define  TIMER0 0 
#define	 TIMER1 1
#define  TIMER2 2
	
/* Modes */
/* Timer 0 */  
#define NORMAL_MODE			0	 
#define CTC					1
#define PHASE_CORRECT		2
#define FASTPWM				3
#define FASTPWM_MODE14		4


/* PreScalers */ 
#define NO_CLOCK			0
#define NO_PRESCALER		1
#define DIV8				8
#define DIV64				64
#define DIV256				256
#define DIV1024				1024


/*Compare Output Mode ,non-PWM Mode */ 
#define OC_DISCONNECTED		0
#define OC_TOGGLE    		1
#define OC_CLEAR			2	
#define OC_SET				3


/* Timer 2 */ 
#define OCR1A_PIN		0
#define OCR1B_PIN		1


/* Timer 1 */ 
#define RISING   0 
#define FALLING  1

/* Media Player */ 

#define NOTE_C4			262
#define NOTE_D4			294
#define NOTE_E4			330
#define NOTE_F4			349
#define NOTE_G4			392
#define NOTE_A4			440
#define NOTE_B4			494
#define NOTE_C5			523
#define NOTE_D5			587
#define NOTE_E5			659
#define NOTE_F5			698
#define NOTE_G5			784
#define NOTE_A5			880
#define NOTE_B5			988
#define  REST			 0

#endif