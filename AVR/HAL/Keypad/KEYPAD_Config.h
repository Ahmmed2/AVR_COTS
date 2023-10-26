#ifndef  _KEYPADCONFIG_
#define  _KEYPADCONFIG_

/* The KeyPad is Pulled up in the Column So the Column is Input */ 

 #define row_start  0 
 #define row_end    4
 #define col_start  0 
 #define col_end    4
 
 
 #define ROW_PORT    PORTC_ID
 #define COLUMN_PORT PORTD_ID
 
 
 /* Calculator */
 #define PLUS			43
 #define MINUS			45	
 #define MULTIPLY       42
 #define DIVISION       47
 #define EQUAL          61
 #define TERMINATE		10

#endif 