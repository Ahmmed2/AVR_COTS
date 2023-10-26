#ifndef  _DIO_INTERFACE_H
#define  _DIO_INTERFACE_H



void DIO_voidSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinDir);
void DIO_voidSetPinValue(u8 Copy_u8PortID,u8 Copy_u8PinID,u8 Copy_u8PinValue);
void DIO_voidSetPortDirection(u8 Copy_u8PortID,u8 Copy_u8PortDir);
void DIO_voidSetPortValue(u8 Copy_u8PortID,u8 Copy_u8PinValue);
u8 DIO_voidgetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID);
void DIO_voidTogglePinValue(u8 Copy_u8PortID , u8 Copy_u8PinID);


void DIO_voidInitialize_CFG();
void DIO_voidSetPortDirection_CFG(u8 Copy_u8PortID);
void DIO_voidSetPortValue_CFG(u8 Copy_u8PortID);
void DIO_voidSetPort_CFG();

void DIO_voidSetPinValue_From_Single_Pin(u8 Copy_u8PinID,u8 Copy_u8PinValue);


#endif
