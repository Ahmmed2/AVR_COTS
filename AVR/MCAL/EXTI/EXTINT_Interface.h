#ifndef  EXT_INT_INTERFACE 
#define  EXT_INT_INTERFACE 


void EXTINT_voidGloblaIniazlize();
void EXTINT_voidEnable(u8 Copy_u8IntNum,u8 Copy_u8SenseMode);
void EXTINT_voidDisable(u8 Copy_u8IntNum);
void EXTINT_voidIntIialize(u8 Copy_u8IntNum);
void EXTINT_voidGloblaDisable();

/* Set Call Back */ 
void EXTINT0_SetCallBack(void(*ptr)(void));
void EXTINT1_SetCallBack(void(*ptr)(void)) ; 
void EXTINT2_SetCallBack(void(*ptr)(void));
#endif 
