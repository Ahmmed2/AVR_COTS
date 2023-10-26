/*
 * Seven_Segment_Interface.h
 *
 * Created: 9/15/2023 9:08:41 AM
 *  Author: Ahmed
 */ 


#ifndef SEVEN_SEGMENT_INTERFACE_H_
#define SEVEN_SEGMENT_INTERFACE_H_



void SevenSegment_voidInit (void ); 

void SevenSegment_voidDisplay(u8 Copy_u8Number , u8 Copy_u8Seg_Number );

void SevenSegment_voidCount();

void SevenSegment_voidWriteNumber(u32 Copy_u8Number);

#endif /* SEVEN_SEGMENT_INTERFACE_H_ */