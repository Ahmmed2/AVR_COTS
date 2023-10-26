
#include "Std_Types.h"
#include "Macros.h"
#include "Kit.h"

#include "SPI_Private.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"

#include "DIO_Interface.h"
#include "DIO_Config.h"


void (*SPI_GPTR)(void)	;


void SPI_voidInialize()
{
	
#if NODE_MODE == POLLING 
	Clear_bit(SPCR,7);
	
#elif NODE_MODE == INTERRUPT 
	Set_bit(SPCR,7);	
#endif
//////////////////////////////////////
	
#if NODE_BIT_SEND == LSB
	Set_bit(SPCR,5);

#elif NODE_BIT_SEND == MSB
	Clear_bit(SPCR,7);
#endif
/////////////////////////////////////

#if NODE_TYPE == MASTER 
	Set_bit(SPCR,4);
#elif NODE_TYPE == SLAVE
	Clear_bit(SPCR,4);
#endif 
/////////////////////////////////////	

#if NODE_CLOCK_POLARITY_PHASE == LEADING_RISING_LEADING_SAMPLE
	Clear_bit(SPCR,3);
	Clear_bit(SPCR,2);	
#elif NODE_CLOCK_POLARITY_PHASE == LEADING_RISING_LEADING_SETUP		
	Clear_bit(SPCR,3);
	Set_bit(SPCR,2);
#elif NODE_CLOCK_POLARITY_PHASE == LEADING_FALLING_LEADING_SAMPLE	
	Set_bit(SPCR,3);
	Clear_bit(SPCR,2);
#elif NODE_CLOCK_POLARITY_PHASE == LEADING_FALLING_LEADING_SETUP	
	Set_bit(SPCR,3);
	Set_bit(SPCR,2);
#endif	
/////////////////////////////////////////

#if NODE_PRE_SCALER == DIV4 		
	Clear_bit(SPCR,0);
	Clear_bit(SPCR,1);
	Clear_bit(SPSR,0);
#elif NODE_PRE_SCALER == DIV16
	Set_bit(SPCR,0);
	Clear_bit(SPCR,1);
	Clear_bit(SPSR,0);
#elif NODE_PRE_SCALER == DIV64
	Clear_bit(SPCR,0);
	Set_bit(SPCR,1);
	Clear_bit(SPSR,0);	
	
#elif NODE_PRE_SCALER == DIV128
	Set_bit(SPCR,0);
	Set_bit(SPCR,1);
	Clear_bit(SPSR,0);	
	
#elif NODE_PRE_SCALER == DIV2
	Clear_bit(SPCR,0);
	Clear_bit(SPCR,1);
	Set_bit(SPSR,0);

#elif NODE_PRE_SCALER == DIV8
	Set_bit(SPCR,0);
	Clear_bit(SPCR,1);
	Set_bit(SPSR,0);

#elif NODE_PRE_SCALER == DIV32
	Clear_bit(SPCR,0);
	Set_bit(SPCR,1);
	Set_bit(SPSR,0);
	
#elif NODE_PRE_SCALER == DIV64
	Set_bit(SPCR,0);
	Set_bit(SPCR,1);
	Set_bit(SPSR,0);
	
#endif
////////////////////////////////////////// 
	
	//SPI Enable
	Set_bit(SPCR,6);
	

}




void SPI_voidTransmiter(u8 Copy_u8Data)
{
#if NODE_MODE == POLLING
	SPDR = Copy_u8Data ;
	while(Get_bit(SPSR,7)==0);

	
#elif NODE_MODE == INTERRUPT
	SPDR = Copy_u8Data ;

#endif 


}

u8 SPI_u8Receiver(void)
{
		while(Get_bit(SPSR,7)==0);
		return SPDR ;
	
}

///////////////////////////////////////////////////////////////

void __vector_12()__attribute__((signal));
void __vector_12()
{
	SPI_GPTR();

}


/* Call Back */

/* SPI Interrupt Call Back  */
void SPI_SetCallBack(void(*ptr)(void))
{
	SPI_GPTR=ptr;
} 