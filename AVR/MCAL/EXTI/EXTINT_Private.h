#ifndef  EXT_INT_PRIVATE 
#define  EXT_INT_PRIVATE 

/*For Global Interrupt */
#define  S_REG          (*((volatile u8*) 0x5F))
#define   I  7
/*For External Interrupts */ 
#define GICR_REG       (*((volatile u8*) 0x5B))
#define INT1 7
#define INT0 6
#define INT2 5

#define  MCUCR_REG      (*((volatile u8*) 0x55))
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define  MCUCSR_REG     (*((volatile u8*) 0x54))
#define ISC2 6

#define  GIFR_REG		(*((volatile u8*) 0x5A))
#define INTF1 7
#define INTF0 6
#define INTF2 5



#endif 
