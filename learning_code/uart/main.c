#include "stm32f10x.h"    
#include "GPIO.h" 
#include "systick.h"

char chat = 'C';

int main(void)
{
// Delays function	
	systick_init();

	//-----------Init UART ------------///
	// Enable the Alternate Function for PINs
		RCC->APB2ENR |= 1;
	// Enable UART2
		RCC->APB1ENR |=0x20000;
	// Enable the related PINs
	init_GP(PA,2,OUT50,O_AF_PP);
	init_GP(PA,3,IN,I_PP);
	// Setup the baude rate for 9600 bps
	USART2->BRR = 0xEA6; 
	// Enable Uart Transmit
	USART2->CR1 |= 8;
	// Enable Uart Recive
	USART2->CR1 |= 4;
	// Enable Uart
	USART2->CR1 |= 0x2000;


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