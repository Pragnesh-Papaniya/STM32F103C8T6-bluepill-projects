#include "stm32f10x.h"    
#include "GPIO.h" 
#include "systick.h"
#include "uart.h"


char chat = 'C';

int main(void)
{
systick_init();
UART_init(2,256000);


while(1)
	{
		// Recieve Char
		while((USART2->SR & 0x20) == 0x00)
		{}
		chat = USART2->DR;
		// Transmit Char
		//DelayMs(100);
		while((USART2->SR & (1<<6)) == 0x40)
		{}
		USART2->DR = chat;
	}
}



