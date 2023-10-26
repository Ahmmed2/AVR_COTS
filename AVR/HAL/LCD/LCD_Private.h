
#ifndef _LCD_PRIVATE_H
#define _LCD_PRIVATE_H

/* Commands */

/*Clear LCD */
#define CLR_LCD       0x01
#define CLR_LCD_H     0b0000
#define CLR_LCD_L     0b0001

/*Function Set */
#define FUNCTION_SET    0b00111000
#define FUNCTION_SET_H  0b0010
#define FUNCTION_SET_L  0b0010
#define FUNCTION_SET_LL 0b1000

/* Display On / OFF */
#define DisplayON_OFF   0b00001110
#define DisplayON_OFF_H 0b0000
#define DisplayON_OFF_L 0b1111

/* Clear Display */
#define CLEAR_DISPLAY   0b00000001
#define CLEAR_DISPLAY_H 0b0000
#define CLEAR_DISPLAY_L 0b0001

/*Entry Mode */
#define ENTRY_MODE   0b00000110 
#define ENTRY_MODE_H 0b0000
#define ENTRY_MODE_L 0b0110

/* Shifting */
#define SHIFTING_H    0b0001

#define SHIFTINGRIGHT_L						0b0100
#define SHIFTINGLEFT_L						0b0000
#define SHIFTING_ENTIRE_DISPLAY_L			0b1000
#define SHIFTING_ENTIRE_DISPLAY_R			0b1100


/* Addresses */

/*To Select Certain Line */
#define DDRAM_BASE_ADDRESS				 0X80
#define FIRST_LINE_ADDRESS				 0X80
#define SECOND_LINE_ADDRESS				 0X80+0X40
#define THIRD_LINE_ADDRESS				 0X80+0X14
#define FOURTH_LINE_ADDRESS				 0X80+0X54

/*For Special Character */
#define CGRAM_BASE_ADDRESS				 0x40
///////////////////////////////////////////////////////////////


#endif 