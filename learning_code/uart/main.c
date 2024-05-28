#include "stm32f10x.h"    
#include "GPIO.h" 
#include "systick.h"
#include "uart.h"

char chat;

int main(void)
{
UART_init(2,256000);
	
	while(1)
	{
		chat = UART_RX(2);
		UART_TX(2,chat);
	}
}
