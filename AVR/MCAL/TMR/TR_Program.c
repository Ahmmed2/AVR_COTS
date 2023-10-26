
#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"
///////////////////////////////
#include "TR_Private.h"
#include "TR_Config.h"
#include "TR_Interface.h"
////////////////////////////////

#include "LCD_Config.h"
#include "LCD_INTERFACE.h"

/* Timer 0 */
void (*TMR0OF_GPTR)(void)	;
void (*TMR0CTC_GPTR)(void)	;
/* Timer 1 */ 
void (*TMR1OF_GPTR)(void)	;
void (*TMR1COMPA_GPTR)(void)	;
void (*TMR1COMPB_GPTR)(void)	;
void (*TMR1CAP_GPTR)(u8)	;
/* Timer 2 */ 
void (*TMR2OF_GPTR)(void)	;
void (*TMR2CTC_GPTR)(void)	;


/* For Delay using CTC  */ 
static u16 CTC_Counter = 0 ;



void TMR0_voidInit(u8 Copy_u8Mode , u8 Copy_u8CompareOPMode)
{
	switch (Copy_u8Mode)
	{
		case NORMAL_MODE :
						/* To Choose Normal Mode */
						Clear_bit(TCCR0,WGM01);
						Clear_bit(TCCR0,WGM00);
						/* To Enable Interrupt Flag */ 
						Set_bit(TIMSK,TOIE0);
					    break ; 
									
		case CTC :	
						/* Enable CTC Mode */ 
						Set_bit(TCCR0,WGM01);
						Clear_bit(TCCR0,WGM00);
						
						if (Copy_u8CompareOPMode==OC_DISCONNECTED)
						{
							Clear_bit(TCCR0,COM00);
							Clear_bit(TCCR0,COM01);	
						}
						else if (Copy_u8CompareOPMode==OC_TOGGLE)
						{
							Set_bit(TCCR0,COM00);
							Clear_bit(TCCR0,COM01);							
						}
						else if (Copy_u8CompareOPMode==OC_SET)
						{
							Clear_bit(TCCR0,COM00);
							Set_bit(TCCR0,COM01);							
						}
						else if (Copy_u8CompareOPMode==OC_CLEAR)
						{
							Set_bit(TCCR0,COM00);
							Set_bit(TCCR0,COM01);							
						}
						
						/* Compare Match Interrupt Enable */ 
						Set_bit(TIMSK,OCIE0);
						break ; 
						
		case PHASE_CORRECT :
						/* Phase Correct PWM Mode */
						Clear_bit(TCCR0,WGM01);
						Set_bit(TCCR0,WGM00);
						
						/* Normal port operation, OC0 disconnected. */
						if (Copy_u8CompareOPMode==OC_DISCONNECTED)
						{
							Clear_bit(TCCR0,COM00);
							Clear_bit(TCCR0,COM01);
						}
						/* Clear OC0 on Compare Match when up-counting. Set OC2 on Compare Match when down counting. */
						else if (Copy_u8CompareOPMode==OC_SET)
						{
							Clear_bit(TCCR0,COM00);
							Set_bit(TCCR0,COM01);
						}
						/* Set OC0 on Compare Match when up-counting. Clear OC2 on Compare Match when down counting.  */
						else if (Copy_u8CompareOPMode==OC_CLEAR)
						{
							Set_bit(TCCR0,COM00);
							Set_bit(TCCR0,COM01);
						}
						break ; 
						
		case FASTPWM :
							/* Fast PWM Mode */
							Set_bit(TCCR0,WGM01);
							Set_bit(TCCR0,WGM00);
							
							/* Normal port operation, OC2 disconnected.*/
							if (Copy_u8CompareOPMode==OC_DISCONNECTED)
							{
								Clear_bit(TCCR0,COM00);
								Clear_bit(TCCR0,COM01);
							}
							/* Clear OC0 on Compare Match, set OC0 at BOTTOM,(non-inverting mode) */
							else if (Copy_u8CompareOPMode==OC_SET)
							{
								
								Clear_bit(TCCR0,COM00);
								Set_bit(TCCR0,COM01);
							}
							/* Set OC0 on Compare Match, clear OC0 at BOTTOM,(inverting mode)  */
							else if (Copy_u8CompareOPMode==OC_CLEAR)
							{
								Set_bit(TCCR0,COM00);
								Set_bit(TCCR0,COM01);
							}

						break ;
		
	}
	
}



void TMR0_voidPreScaler(u8 Copy_u8DIV)
{
	switch(Copy_u8DIV)
	{
		
		case NO_CLOCK	  :		
								Clear_bit(TCCR0,CS00)	;
								Clear_bit(TCCR0,CS01)	;
								Clear_bit(TCCR0,CS02)	;
								break;
		case NO_PRESCALER :	    
								Set_bit(TCCR0,CS00)	;
								Clear_bit(TCCR0,CS01)	;
								Clear_bit(TCCR0,CS02)	;			
								break;
		case DIV8		  :	
								Clear_bit(TCCR0,CS00)	;
								Set_bit(TCCR0,CS01)	    ;
								Clear_bit(TCCR0,CS02)	;	
								break;
								
		case DIV64		  :	
								Set_bit(TCCR0,CS00)	    ;
								Set_bit(TCCR0,CS01)	    ;
								Clear_bit(TCCR0,CS02)	;
// 								TCCR0 |= 1<<CS00 | 1<<CS01 | 0<<CS02 ;
								break;
								
		case DIV256		  :		
								Clear_bit(TCCR0,CS00)	;
								Clear_bit(TCCR0,CS01)	;
								Set_bit(TCCR0,CS02)		;	
								break;
								
		case DIV1024	  :	
								 Set_bit(TCCR0,CS00)	;
								 Clear_bit(TCCR0,CS01)	;
								 Set_bit(TCCR0,CS02)	;	
								 break;
							
		
	}
	
}

void TMR02_voidPreLoad (u8 Copy_u8Timer , u8 Copy_u8Mode , u8 Copy_u8Value  )
{
	
	switch (Copy_u8Timer)
	{
		
		
		
		case TIMER0 : 
		             if (Copy_u8Mode == NORMAL_MODE )
					 {
						 TCNT0=Copy_u8Value;
					 }
					 else if (Copy_u8Mode == CTC)
					 {
						  /* Start Count from it */
						  OCR0=Copy_u8Value;
					 }
					 else if (Copy_u8Mode == PHASE_CORRECT) 
					 {
						  OCR0=Copy_u8Value;
					 }
					 else if (Copy_u8Mode == FASTPWM)
					 {
						 OCR0=Copy_u8Value;
					 }
					 break ;
					
					 
		case TIMER2 :
				     if (Copy_u8Mode == NORMAL_MODE )
					 {
						 TCNT2=Copy_u8Value;
					 }
				     else if (Copy_u8Mode == CTC )
					 {
						  OCR2=Copy_u8Value;
					 }
					 else if (Copy_u8Mode == PHASE_CORRECT )
					 {
						 OCR2=Copy_u8Value;
					 }
					 else if (Copy_u8Mode == FASTPWM)
					 {
						  OCR2=Copy_u8Value;
					 }
					 break ; 
	}
	
	
}




/* Function Argument is the delay in the ms */ 
/* This Function works Correctly when the pre_scaler is DIV64 */

void TMR02_voidSetDelayUsingCTC (u8 Copy_u8Timer , u16 Copy_u16Value )
{
	if (Copy_u8Timer == TIMER0)
	{
	/* Under Condition of Tick Time = 4ms (Pre_Scaler DIV64 ) */ 
	 OCR0 = 249 ; 
	
	/* CTC_Counter = (copy_u16Value * 1000 ) /1000  */
	 CTC_Counter = Copy_u16Value  ;
	}
	else if (Copy_u8Timer == TIMER2)
	{
	/* Under Condition of Tick Time = 4ms (Pre_Scaler DIV64 ) */
	OCR2 = 249 ;
	
	/* CTC_Counter = (copy_u16Value * 1000 ) /1000  */
	CTC_Counter = Copy_u16Value  ;
	}
}


/* This Function takes the DUTY cycle in percentage , also it works only for DIV64 pre_scaler */ 
void TMR02_voidSetDutyCycle (u8 Copy_u8Timer , u8 Copy_u8DutyValue ,u8 Copy_u8Mode )
{
	u32 Local_u32Temp = 0 ;
	
	if (Copy_u8Mode == OC_SET)
	{
		Local_u32Temp = (Copy_u8DutyValue) * (256) ;
		Local_u32Temp = Local_u32Temp / 100 ;
		Local_u32Temp = Local_u32Temp - 1 ;
	}	
	else if (Copy_u8Mode == OC_CLEAR)
	{
		Copy_u8DutyValue = 100 - Copy_u8DutyValue ;
		Local_u32Temp = (Copy_u8DutyValue) * (256) ;
		Local_u32Temp = Local_u32Temp / 100 ;
		Local_u32Temp = Local_u32Temp - 1 ;
	}
	
	if ( Copy_u8DutyValue == 0 )
	{
		Local_u32Temp = 0 ;
	}
	
	switch (Copy_u8Timer)
	{
		
		case TIMER0 :	OCR0 = 	Local_u32Temp ; 	 break ;
						
		case TIMER2 :  	OCR2 = 	Local_u32Temp ;      break ;
	}
}


void TMR0_voidDisable(void)
{
	TMR0_voidPreScaler(NO_CLOCK);
}


u8 TMR_voidMappingSpeed (u8 Copy_u8Value)
{
	u8 Local_u8Amplitude = 5 ;
	u8 Local_u8DutyCycle = 0 ;
	/* Effective Voltage = Amp Sqrt(DutyCycle) */
	Local_u8DutyCycle = (Copy_u8Value *10/Local_u8Amplitude) * (Copy_u8Value*10 /Local_u8Amplitude) ;
	return Local_u8DutyCycle ;
	
}








/* Timer1 */ 
void TMR1_voidInit(u8 Copy_u8Mode , u8 Copy_u8Channel , u8 Copy_u8CompareOPMode)
{
	switch (Copy_u8Mode)
	{
		case NORMAL_MODE :
							Clear_bit(TCCR1A,WGM10);
							Clear_bit(TCCR1A,WGM11);
							Clear_bit(TCCR1B,WGM12);
							Clear_bit(TCCR1B,WGM13);
							if ( Copy_u8Channel == OCR1A_PIN )
							{	
							/* To Choose Normal Mode on OCR1A */
							Clear_bit(TCCR1A,COM1A1);
							Clear_bit(TCCR1A,COM1A0);
							}
							else if (Copy_u8Channel == OCR1B_PIN)
							{
							/* To Choose Normal Mode on OCR1B */
							Clear_bit(TCCR1B,COM1A1);
							Clear_bit(TCCR1B,COM1A0);
							}
							/* To Enable Interrupt Flag */
							Set_bit(TIMSK,TOIE1);
							break ;
			
		case CTC :
							Clear_bit(TCCR1A,WGM10);
							Clear_bit(TCCR1A,WGM11);
							Set_bit(TCCR1B,WGM12);
							Clear_bit(TCCR1B,WGM13);
							if ( Copy_u8Channel == OCR1A_PIN )
							{
								if (Copy_u8CompareOPMode == OC_DISCONNECTED)
								{
									Clear_bit(TCCR1A,COM1A1);
									Clear_bit(TCCR1A,COM1A0);
								}
								else if (Copy_u8CompareOPMode == OC_TOGGLE)
								{
									Clear_bit(TCCR1A,COM1A1);
									Set_bit(TCCR1A,COM1A0);									
								}
								else if (Copy_u8CompareOPMode == OC_CLEAR)
								{
									Set_bit(TCCR1A,COM1A1);
									Clear_bit(TCCR1A,COM1A0);									
								}
								else if (Copy_u8CompareOPMode == OC_SET)
								{
									Set_bit(TCCR1A,COM1A1);
									Set_bit(TCCR1A,COM1A0);
								}	
									/* Compare Match Interrupt Enable */
									Set_bit(TIMSK,OCIE1A);

							}
							else if (Copy_u8Channel == OCR1B_PIN)
							{
								if (Copy_u8CompareOPMode == OC_DISCONNECTED)
								{
									Clear_bit(TCCR1B,COM1B1);
									Clear_bit(TCCR1B,COM1B0);
								}
								else if (Copy_u8CompareOPMode == OC_TOGGLE)
								{
									Clear_bit(TCCR1B,COM1B1);
									Set_bit(TCCR1B,COM1B0);
								}
								else if (Copy_u8CompareOPMode == OC_CLEAR)
								{
									Set_bit(TCCR1B,COM1B1);
									Clear_bit(TCCR1B,COM1B0);
								}
								else if (Copy_u8CompareOPMode == OC_SET)
								{
									Set_bit(TCCR1B,COM1B1);
									Set_bit(TCCR1B,COM1B0);
								}
									/* Compare Match Interrupt Enable */
									Set_bit(TIMSK,OCIE1B);
							}
							
							break ;
				

			  case FASTPWM_MODE14 :	
							/* Mode 14 Fast PWM */
							Clear_bit(TCCR1A,WGM10);
							Set_bit(TCCR1A,WGM11);
							Set_bit(TCCR1B,WGM12);
							Set_bit(TCCR1B,WGM13);
							if ( Copy_u8Channel == OCR1A_PIN )
							{
								if (Copy_u8CompareOPMode == OC_DISCONNECTED)
								{
									Clear_bit(TCCR1A,COM1A1);
									Clear_bit(TCCR1A,COM1A0);
								}
								else if (Copy_u8CompareOPMode == OC_CLEAR)
								{
									Set_bit(TCCR1A,COM1A1);
									Clear_bit(TCCR1A,COM1A0);
								}
								else if (Copy_u8CompareOPMode == OC_SET)
								{
									Set_bit(TCCR1A,COM1A1);
									Set_bit(TCCR1A,COM1A0);
								}


							}
							else if (Copy_u8Channel == OCR1B_PIN)
							{
								if (Copy_u8CompareOPMode == OC_DISCONNECTED)
								{
									Clear_bit(TCCR1B,COM1B1);
									Clear_bit(TCCR1B,COM1B0);
								}
								/* Set OC1A/OC1B on compare match, clear OC1A/OC1B at TOP */ 
								else if (Copy_u8CompareOPMode == OC_CLEAR)
								{
									Set_bit(TCCR1B,COM1B1);
									Clear_bit(TCCR1B,COM1B0);
								}
								/* Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM,(non-inverting mode) */
								else if (Copy_u8CompareOPMode == OC_SET)
								{
									Set_bit(TCCR1B,COM1B1);
									Set_bit(TCCR1B,COM1B0);
								}
							}									
			  
									break ; 		
	}
	
	

}



void TMR1_voidPreScaler (u8 Copy_u8DIV)
{
	switch (Copy_u8DIV)
	{
		case NO_CLOCK	  :
								Clear_bit(TCCR1B,CS10)	;
								Clear_bit(TCCR1B,CS11)	;
								Clear_bit(TCCR1B,CS12)	;
								break;
		case NO_PRESCALER :
								Set_bit(TCCR1B,CS10)	;
								Clear_bit(TCCR1B,CS11)	;
								Clear_bit(TCCR1B,CS12)	;
								break;
		case DIV8		  :
								Clear_bit(TCCR1B,CS10)	;
								Set_bit(TCCR1B,CS11)	    ;
								Clear_bit(TCCR1B,CS12)	;
								break;
		
		case DIV64		  :
								Set_bit(TCCR1B,CS10)	    ;
								Set_bit(TCCR1B,CS11)	    ;
								Clear_bit(TCCR1B,CS12)	;
								break;
		
		case DIV256		  :
								Clear_bit(TCCR1B,CS10)	;
								Clear_bit(TCCR1B,CS11)	;
								Set_bit(TCCR1B,CS12)		;
								break;
		
		case DIV1024	  :
								Set_bit(TCCR1B,CS10)	;
								Clear_bit(TCCR1B,CS11)	;
								Set_bit(TCCR1B,CS12)	;
								break;
	}
			
}











void TMR1_voidPreload(u8 Copy_u8Mode ,u8 Copy_u8Channel , u16 Copy_u16Value)
{
	switch ( Copy_u8Mode  )
	{
		case NORMAL_MODE : 
								TCNT1 = Copy_u16Value ; 
								break ;
		case CTC         : 
								if (Copy_u8Channel == OCR1A_PIN)
								{
									OCR1A = Copy_u16Value ;
								}
								else if (Copy_u8Channel == OCR1B_PIN)
								{
									OCR1B = Copy_u16Value ;
								}
								break ;
								
		case FASTPWM_MODE14 : 
								if (Copy_u8Channel == OCR1A_PIN)
								{
									OCR1A = Copy_u16Value ;
								}
								else if (Copy_u8Channel == OCR1B_PIN)
								{
									OCR1B = Copy_u16Value ;
								}
								break ;
									
		
	}
	

	
}

void TMR1_voidSetFreq(u16 Copy_u16Freq)
{
	
	
	u16 Local_u16Temp = 0 ; 
	Local_u16Temp = ((1000000/(Copy_u16Freq*4))-1) ;
	ICR1 = Local_u16Temp ;
	
	
}


void TMR1_voidSetDutyDependonICR1 (u16 Copy_u8DutyValue )
{
	u16 Local_Duty = (ICR1 * Copy_u8DutyValue ) /100 ;
	/*Local_Duty =  (Local_Duty *10)/10  ;*/
	
	OCR1A = (u16)Local_Duty ;
	LCD_voidDisplayNumber((u32)OCR1A);
	
	
}

void TMR1_voidServoAngleControl(s8 Copy_u8Angle)
{
		f32 Local_f32angle = 0 ;
		Local_f32angle = ((f32)(Copy_u8Angle)/ 180  )+ 1.5 ;
		Local_f32angle = (Local_f32angle * 1000 ) / 4  ;
		Local_f32angle = Local_f32angle - 1 ;
		OCR1A = Local_f32angle ;
		
}
void TMR1_voidEnableInputCaptureInterrupt ()
{
		/* Enable Input Capture Interrupt */
		Set_bit(TIMSK,TICIE1) ;
	
}
void TMR1_voidCaptureEdgeSelect (u8 Copy_EdgeSelect)
{

	switch (Copy_EdgeSelect)
	{
		
		case RISING :  Set_bit(TCCR1B,ICES1)   ;  break ;
		
		case FALLING : Clear_bit(TCCR1B,ICES1) ;  break ;
	}
}

u8 TMR1_voidCapturePWM () 
{
	u16 Local_u8FallingEdge = 0 ;
	u16 Local_u8RisingEdge1 = 0 ;
	u16 Local_u8RisingEdge2 = 0 ;
	u16 Local_u8Ton = 0 ;
	


	//Rising 
	TMR1_voidCaptureEdgeSelect (FALLING) ;
	while (Get_bit(TIFR,ICF1)==0) ;
	Local_u8RisingEdge1 = ICR1 ;
	Set_bit(TIFR,ICF1) ;
	
	//Falling
	TMR1_voidCaptureEdgeSelect (RISING) ;
	while (Get_bit(TIFR,ICF1)==0) ;
	Local_u8FallingEdge = ICR1 ;
	Set_bit(TIFR,ICF1) ;
	
	//Rising
	TMR1_voidCaptureEdgeSelect (FALLING) ;
	while (Get_bit(TIFR,ICF1)==0) ;
/*	Local_u8RisingEdge2 = ICR1 - Local_u8FallingEdge ;*/
	Local_u8RisingEdge2 = ICR1 ;
	Set_bit(TIFR,ICF1) ;
	
	

	
	//Local_u8Ton = Local_u8FallingEdge - Local_u8RisingEdge ;
	//TCCR1B = 0 ;
	
	//Local_u8RisingEdge1 0 
	//Local_u8FallingEdge 129
	//Local_u8RisingEdge2 129
	return Local_u8FallingEdge ;
	
	
}

void TMR1_voidDisable(void)
{
	TMR1_voidPreScaler(NO_CLOCK) ;
}






// void TMR1_voidServo_GetAngle(u8 Copy_u8Angle)
// {
// 	u32 timer ;
// 	f32 slope ;
// 
// 	 TR1_voidTR1Normal_Init();
// 	/* the below equation : range value from the stepper to go from 0 to 180  is from 999 to 1999 by trails
// 		and the range of angles from  Servo is from 0 to 180 then make equation of straight line and that will appear*/
// 	slope=50.0/9 ;
// 	timer=slope*Copy_u8Angle+999 ;
// 	TR1_voidTR1_Preload(timer);
// 
// }






/* Timer 2 */ 
void TMR2_voidInit(u8 Copy_u8Mode , u8 Copy_u8CompareOPMode)
{
	switch (Copy_u8Mode)
	{
		case NORMAL_MODE :
							/* To Choose Normal Mode */
							Clear_bit(TCCR2,WGM21);
							Clear_bit(TCCR2,WGM20);
							/* To Enable Interrupt Flag */
							Set_bit(TIMSK,TOIE2);
							break ;
		
		case CTC :
							/* Enable CTC Mode */
							Set_bit(TCCR2,WGM21);
							Clear_bit(TCCR2,WGM20);
							/* Choose the Action on OC pin */
							if (Copy_u8CompareOPMode==OC_DISCONNECTED)
							{
								Clear_bit(TCCR2,COM20);
								Clear_bit(TCCR2,COM21);
							}
							else if (Copy_u8CompareOPMode==OC_TOGGLE)
							{
								Set_bit(TCCR2,COM20);
								Clear_bit(TCCR2,COM21);
							}
							else if (Copy_u8CompareOPMode==OC_SET)
							{
								Clear_bit(TCCR2,COM20);
								Set_bit(TCCR2,COM21);
							}
							else if (Copy_u8CompareOPMode==OC_CLEAR)
							{
								Set_bit(TCCR2,COM20);
								Set_bit(TCCR2,COM21);
							}
							
							/* Compare Match Interrupt Enable */
							Set_bit(TIMSK,OCIE2);
							break ;
		
		case PHASE_CORRECT :
							/* PWM Mode */
							Clear_bit(TCCR2,WGM21);
							Set_bit(TCCR2,WGM20);
							/* Normal port operation, OC2 disconnected. */
							if (Copy_u8CompareOPMode==OC_DISCONNECTED)
							{
								Clear_bit(TCCR2,COM20);
								Clear_bit(TCCR2,COM21);
							}
							/* Clear OC2 on Compare Match when up-counting. Set OC2 on Compare Match when down counting. */ 
							else if (Copy_u8CompareOPMode==OC_SET)
							{
								Clear_bit(TCCR2,COM20);
								Set_bit(TCCR2,COM21);
							}
							/* Set OC2 on Compare Match when up-counting. Clear OC2 on Compare Match when down counting.  */
							else if (Copy_u8CompareOPMode==OC_CLEAR)
							{
								Set_bit(TCCR2,COM20);
								Set_bit(TCCR2,COM21);
							}
							break ;
		
		case FASTPWM :
							/* Fast PWM Mode */
							Set_bit(TCCR2,WGM21);
							Set_bit(TCCR2,WGM20);
							/* Normal port operation, OC2 disconnected.*/
							if (Copy_u8CompareOPMode==OC_DISCONNECTED)
							{
								Clear_bit(TCCR2,COM20);
								Clear_bit(TCCR2,COM21);
							}
							/* Clear OC2 on Compare Match, set OC2 at BOTTOM,(non-inverting mode) */
							else if (Copy_u8CompareOPMode==OC_SET)
							{
								Clear_bit(TCCR2,COM20);
								Set_bit(TCCR2,COM21);
							}
							/* Set OC2 on Compare Match, clear OC2 at BOTTOM,(inverting mode)  */
							else if (Copy_u8CompareOPMode==OC_CLEAR)
							{
								Set_bit(TCCR2,COM20);
								Set_bit(TCCR2,COM21);
							}

							break ;
		
	}
	
}


void TMR2_voidPreScaler(u8 Copy_u8DIV)
{
	
		switch(Copy_u8DIV)
		{
			
			case NO_CLOCK	  :
			Clear_bit(TCCR2,CS20)	;
			Clear_bit(TCCR2,CS21)	;
			Clear_bit(TCCR2,CS22)	;
			break;
			case NO_PRESCALER :
			Set_bit(TCCR2,CS20)	;
			Clear_bit(TCCR2,CS21)	;
			Clear_bit(TCCR2,CS22)	;
			break;
			case DIV8		  :
			Clear_bit(TCCR2,CS20)	;
			Set_bit(TCCR2, CS21)	;
			Clear_bit(TCCR2,CS22)	;
			break;
			
			case DIV64		  :
			Set_bit(TCCR2,CS20)		;
			Set_bit(TCCR2,CS21)		;
			Clear_bit(TCCR2,CS22)	;
			break;
			
			case DIV256		  :
			Clear_bit(TCCR2,CS20)	;
			Clear_bit(TCCR2,CS21)	;
			Set_bit(TCCR2,CS22 )	;
			break;
			
			case DIV1024	  :
			Set_bit(TCCR2,CS20)		;
			Clear_bit(TCCR2,CS21)	;
			Set_bit(TCCR2,CS22)		;
			break;
			
			
		}
}




void TMR2_voidDisable(void)
{
	TMR2_voidPreScaler(NO_CLOCK);
}











////////////////////////////////////////////////////////////////////////////

/* Timer 0 OverFlow */ 
void __vector_11()__attribute__((signal));
void __vector_11()
{
	TMR0OF_GPTR() ;	
}

/* Timer 0 Compare Match */
void __vector_10()__attribute__((signal));
void __vector_10()
{

	static u16 Counter = 0 ;
	Counter ++ ;
	if (Counter == CTC_Counter )
	{
		Counter = 0 ;
		TMR0CTC_GPTR();
	}
}


/* Timer 1 OverFlow */
void __vector_9()__attribute__((signal));
void __vector_9()
{

		TMR1OF_GPTR();
}

/* Timer 1 CompareB */
void __vector_8()__attribute__((signal));
void __vector_8()
{

	TMR1COMPB_GPTR();
}

/* Timer 1 CompareA */
void __vector_7()__attribute__((signal));
void __vector_7()
{

	TMR1COMPA_GPTR();
}

/* Timer 1 Capture */
void __vector_6()__attribute__((signal));
void __vector_6()
{

	TMR1CAP_GPTR(ICR1);
}


/* Timer 2 OF */
void __vector_5()__attribute__((signal));
void __vector_5()
{
	TMR2OF_GPTR();

}

/* Timer 2 Compare */
void __vector_4()__attribute__((signal));
void __vector_4()
{
	TMR2CTC_GPTR();

}


////////////////////////////////////////////////////////////////////////////////////

/* Timer 0 OverFlow CallBack Function */ 
void TMR0INTOF_SetCallBack(void(*ptr)(void))
{
	TMR0OF_GPTR=ptr;
}


/* Timer 0 Compare CallBack Function */ 
 void TMR0INTCompare_SetCallBack(void(*ptr)(void))
{
	TMR0CTC_GPTR=ptr;
} 

/* Timer1 OverFlow CallBack Function */
void TMR1INTOF_SetCallBack(void(*ptr)(void))
{
	TMR1OF_GPTR=ptr;
}

/* Timer 1 CompareB CallBack Function */
void TMR1INTCompareB_SetCallBack(void(*ptr)(void))
{
	TMR1COMPB_GPTR=ptr;
}

/* Timer 1 CompareA CallBack Function */
void TMR1INTCompareA_SetCallBack(void(*ptr)(void))
{
	TMR1COMPA_GPTR=ptr;
}

/* Timer 1 Capture CallBack Function */
void TMR1INTCapture_SetCallBack(void(*ptr)(u8))
{
	TMR1CAP_GPTR=ptr;
}

/* Timer 2 OverFlow CallBack Function */
void TMR2INTOF_SetCallBack(void(*ptr)(void))
{
	TMR2OF_GPTR=ptr;
}


/* Timer 2 Compare CallBack Function */
void TMR2INTCompare_SetCallBack(void(*ptr)(void))
{
	TMR2CTC_GPTR=ptr;
}