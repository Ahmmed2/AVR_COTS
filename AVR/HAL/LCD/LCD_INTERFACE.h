#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H



void LCD_voidInit(void);

/* 4-BIT LCD */ 
void LCD_voidWriteCommand_4L(u8 Copy_u8Value ) ;
void LCD_voidWrite_Data_4L(u8 Copy_u8Value );
void LCD_voidEnable_4L();
void LCD_voidSendDATA_4L(u8 Copy_u8DATA);



/* 8-Bit LCD */ 
void LCD_voidWriteCommand_8L(u8 Copy_u8Command);
void LCD_voidWriteDATA_8L(u8 Copy_u8DATA);

void LCD_GoToXY(u8 X, u8 Y);
void LCD_voidWriteSting(u8 *Copy_u8string ,  u8 Copy_u8Line );
void LCD_voidDisplayNumber(u32 Copy_u8DATA);
void LCD_voidWriteSpecialCharacter(u8 Copy_u32arr[8],u8 Copy_u8Pattern_Number , u8 Copy_u8Line , u8 Copy_u8Offset );
void LCD_voidShift(u8 Copy_u8ShifttingDirection);
void LCD_voidClear();



/* Communicate Through IC-74HC595"Serial To parallel Converter  */ 
void LCD_voidInit_IC(void) ;
void LCD_voidWriteDataIC_4L(u8 Copy_u8Command)  ;
void LCD_EnableICPulse ()	;
void LCD_voidClearIC_4L () ; 

#endif
