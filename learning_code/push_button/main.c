#include "stm32f10x.h"                  // Device header
#include "GPIO.h"

void systick_init(void);
void exti_init(void);
volatile int signal = 0;				// high when button pressed
volatile unsigned long count=0;	// when it is 10; 0.1*10=1 sec delay generated

int main(void)
{
	init_GP(PA,0,IN,I_PP); 					// push button
	init_GP(PC,13,OUT50, O_GP_PP);	// in-built led
	exti_init();
	
	while(1)
	{
		
	}
}

void systick_init(void)
{
	__disable_irq();						// to avoid race condition
	SysTick->CTRL = 0;
	SysTick->LOAD = 7200000-1;	// 0.1 sec delay
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;					// interrupt enabled
	__enable_irq();
}

void exti_init(void)
{
	__disable_irq();								// to avoid race condition
	AFIO->EXTICR[0] = 0x00; /// Activating the interrupts for the Port A PIN 0
	EXTI->IMR |= 1; /// Enable the interrupt for EXTI0
	EXTI->RTSR |= 1; /// Generate a system interrupt at the rising edge
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable the global interrupt function
	__enable_irq();
}

void SysTick_Handler(void)
{
	count++;									// goal is to make it 10	
	if((count==10) && signal) /// Checking status of PIN ! portA and after 0.1*10 = 1 sec delay 
	{
		count=1;
		toggle_GP(PC,13); /// Toggle the PIN state
	}
	else
	{
		W_GP(PC,13,1); /// Set the PIN 13 port C high if button is not pressed
	}
}

void EXTI0_IRQHandler() // Interrupt Handler function for Port A pin 0
{
	systick_init();
	EXTI->PR |=1;					// resetting pending bit so it doesn't get stuck in ISR
	if(signal)						// keeping ISR short
	{signal = 0;}
	else
	{signal = 1;}
}
