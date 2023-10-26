#ifndef  TR_INTERFACE
#define  TR_INTERFACE

																/*			Timer0 , Timer2			*/

/* Initialization */
void TMR0_voidInit(u8 Copy_u8Mode , u8 Copy_u8CompareOPMode) ;
void TMR2_voidInit(u8 Copy_u8Mode , u8 Copy_u8CompareOPMode);
void TMR0_voidPreScaler(u8 Copy_u8DIV);
void TMR2_voidPreScaler(u8 Copy_u8DIV);
void TMR0_voidDisable(void) ;
void TMR2_voidDisable(void);

/* Normal and CTC Mode */
void TMR02_voidPreLoad (u8 Copy_u8Timer , u8 Copy_u8Mode , u8 Copy_u8Value) ;
void TMR02_voidSetDelayUsingCTC (u8 Copy_u8Timer , u16 Copy_u16Value ) ;


/* PWM Mode */ 
void TMR02_voidSetDutyCycle (u8 Copy_u8Timer ,u8 Copy_u8DutyValue,u8 Copy_u8Mode) ;
u8 TMR_voidMappingSpeed (u8 Copy_u8Value) ;



																/*				Timer1					*/ 
void TMR1_voidInit(u8 Copy_u8Mode , u8 Copy_u8Channel,u8 Copy_u8CompareOPMode) ;
void TMR1_voidPreScaler (u8 Copy_u8DIV) ; 
void TMR1_voidPreload(u8 Copy_u8Mode ,u8 Copy_u8Channel , u16 Copy_u16Value) ; 
void TMR1_voidSetFreq(u16 Copy_u16Freq) ;	
void TMR1_voidSetDutyDependonICR1 (u16 Copy_u8DutyValue ) ;	
void TMR1_voidCaptureEdgeSelect (u8 Copy_EdgeSelect) ;
u8 TMR1_voidCapturePWM () ;
void TMR1_voidEnableInputCaptureInterrupt () ;
void TMR1_voidDisable(void) ;

/* For Servo */ 
void TMR1_voidServoAngleControl(s8 Copy_u8Angle ) ;	
		
		
		

/* Call Back */ 
void TMR0INTOF_SetCallBack(void(*ptr)(void)) ; 
void TMR0INTCompare_SetCallBack(void(*ptr)(void)) ; 
void TMR1INTOF_SetCallBack(void(*ptr)(void)) ;
void TMR1INTCompareB_SetCallBack(void(*ptr)(void)) ;
void TMR1INTCompareA_SetCallBack(void(*ptr)(void)) ;
void TMR1INTCapture_SetCallBack(void(*ptr)(u8)) ;
void TMR2INTOF_SetCallBack(void(*ptr)(void)) ;
void TMR2INTCompare_SetCallBack(void(*ptr)(void)) ;

#endif
