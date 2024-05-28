#include "stm32f10x.h"  
#include "GPIO.h" 

unsigned long USART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
