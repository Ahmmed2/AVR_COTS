/*
 * StackBasedCalculator_Interface.h
 *
 * Created: 9/21/2023 4:28:28 PM
 *  Author: Ahmed
 */ 


#ifndef STACKBASEDCALCULATOR_INTERFACE_H_
#define STACKBASEDCALCULATOR_INTERFACE_H_


/* First Stack */
s8 isEmpty_FirstStack() ;
u8 isFull_FirstStack() ;
u8 Peek_FirstStack()  ;
s8 POP_FirstStack() ;
void Push_FirstStack(u8 oper) ;
int checkIfOperand(u8 Number)  ;
s8 precedence(u8 Operator)  ;
s8 covertInfixToPostfix(u8 *Expression )  ;
/* Second Stack */
void Push_SecondStack (u8 data );
u8  POP_SecondStack ();
void Calc_Result (u8 arr[]) ;

/* Third Stack */ 
void push(char c) ;
char pop() ;
void pre_post() ;



/* To Take Input from User */ 
void StackBasedCalculator_voidShowInput () ;
#endif /* STACKBASEDCALCULATOR_INTERFACE_H_ */