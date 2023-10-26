/*
 * RTC_Interface.h
 *
 * Created: 9/30/2023 3:03:34 PM
 *  Author: Ahmed
 */ 


#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

void RTC_voidInit () ;
void RTC_voidWriteData (u8 Copy_u8Address , u8 Copy_u8Data);
u8 RTC_voidReadData (u8 Copy_u8Address) ;


#endif /* RTC_INTERFACE_H_ */