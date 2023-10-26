/*
 * RTC_Program.c
 *
 * Created: 9/30/2023 3:03:53 PM
 *  Author: Ahmed
 */ 

#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "DIO_Config.h"
#include "DIO_Interface.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"


#include "RTC_Private.h"
#include "RTC_Config.h"
#include "RTC_Interface.h"


void RTC_voidInit () 
{
	
	TWI_voidInitMaster (0xFF) ; 
}


void RTC_voidWriteData (u8 Copy_u8Address , u8 Copy_u8Data)
{
	u8 Local_u8Temp = Copy_u8Address ;  
	
	// Send Start Condition
	TWI_voidStartCondition () ;
	// Send Slave Address
	TWI_voidSendSlaveAdressWithWrite(Local_u8Temp) ;
	// Send Byte Data
	TWI_voidSendMasterDataByte(Copy_u8Data) ;
	// Send Stop Condition
	TWI_voidStopCondition() ;

}


u8 RTC_voidReadData (u8 Copy_u8Address)
{
	
	u8 Local_u8RxValue ;
	
	u8 Local_u8Temp = Copy_u8Address  ;
	/* Frame Sequence */
	// Send Start Condition
	TWI_voidStartCondition () ;
	//Send Slave Address with read
	TWI_voidSendSlaveAdressWithRead(Copy_u8Address) ;
	//Receive Data
	Local_u8RxValue = TWI_voidReceiveMasterDataByte () ;
	//Send Stop Condition
	TWI_voidStopCondition() ;

	

	return Local_u8RxValue ;
}