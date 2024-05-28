#include "stm32f10x.h"    
#include "gp_drive.h" 
#include "systick_time.h"
#include "uart_drive.h"

char USART_1_msg[250];
unsigned short USART_1_cnt = 0;
unsigned short USART_1_sig = 0;
unsigned short USART_1_bdg = 0;

char USART_2_msg[250];
unsigned short USART_2_cnt = 0;
unsigned short USART_2_sig = 0;
unsigned short USART_2_bdg = 0;

char USART_3_msg[250];
unsigned short USART_3_cnt = 0;
unsigned short USART_3_sig = 0;
unsigned short USART_3_bdg = 0;

int main(void)
{
systick_init();
UART_init(2,115200);
UART_init(3,115200);

DelayMs(100);

UART_SEND(2,"This is UART 2");
UART_SEND(3,"This is UART 3");
	
	while(1)
	{
		if(USART_2_sig == 1)
		{
			UART_SEND(3,USART_2_msg);
			USART_2_sig = 0;
			str_empty(USART_2_msg);
		}
		if(USART_3_sig == 1)
		{
			UART_SEND(2,USART_3_msg);
			USART_3_sig = 0;
			str_empty(USART_3_msg);
		}
	}
}

void USART2_IRQHandler()
{
	UART_ISR(2,3,&USART_2_sig, &USART_2_cnt, USART_2_msg);
//UART_ISR(2,0,&USART_2_sig, &USART_2_cnt, USART_2_msg);	for processing/different baud rates
}

void USART3_IRQHandler()
{
	UART_ISR(3,2,&USART_3_sig, &USART_3_cnt, USART_3_msg);
//UART_ISR(3,2,&USART_3_sig, &USART_3_cnt, USART_3_msg);  for processing/different baud rates
}

