#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
	
#define LED_RED (1<<1)
#define LED_BLUE (1<<2)
#define LED_GREEN (1<<3)


#include "tm4c123gh6pm.h"
int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	RCGCGPIO |= 0x20;
		SYSCTL_GPIOHBCTL_R |= (1<<5); //enable AHB bus for PORTF
	volatile unsigned int delay = 0;
    while(delay < 200) delay++;
	GPIO_PORTF_AHB_DIR_R = 0x0E;
	GPIO_PORTF_AHB_DEN_R = 0x0E;
	GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;

	while(1){
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
		GPIO_PORTF_AHB_DATA_R |= (1<<1);
	for(volatile unsigned int i = 0; i < 700000; i++) {}
		
	
	GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
		for(volatile unsigned int i = 0; i < 700000; i++) {}
	}
}