#include "stm32f10x.h"                  // Device header
#include "GPIO.h"

void DelayMillis(unsigned long t);
void systick_init(void);
int signal = 0;

int main(void)
{
	init_GP(PA,0,IN,I_PP); 					// push button
	init_GP(PC,13,OUT50, O_GP_PP);	// in-built led
	
	__disable_irq();								// to avoid race condition
	AFIO->EXTICR[0] = 0x00; /// Activating the interrupts for the Port A PIN 0
	EXTI->IMR |= 1; /// Enable the interrupt for EXTI0
	EXTI->RTSR |= 1; /// Generate a system interrupt at the rising edge
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable the global interrupt function
	__enable_irq();
	
	while(1)
	{
		if(signal) /// Checking status of PIN ! portA 
		{
			DelayMillis(1000);
			toggle_GP(PC,13); /// Toggle the PIN state
			DelayMillis(1000);
		}
		else
		{
			W_GP(PC,13,1); /// Set the PIN 13 port C high
		}
	}
}

void systick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
}

void DelayMillis(unsigned long t)
{
	for(;t>0;t--)
	{
		SysTick->LOAD = 0x11940;
		SysTick->VAL = 0;
		while((SysTick->CTRL & 0x00010000) == 0);
	}
}

void EXTI0_IRQHandler() // Interrupt Handler function for Port A pin 0
{
	EXTI->PR |=1;					// resetting pending bit so it doesn't get stuck in ISR
	if(signal)						// keeping ISR short
	{signal = 0;}
	else
	{signal = 1;}
}
