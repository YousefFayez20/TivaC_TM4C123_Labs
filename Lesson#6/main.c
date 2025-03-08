#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
	
#include "tm4c123gh6pm.h"
int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	RCGCGPIO |= 0x20;
	volatile unsigned int delay = 0;
    while(delay < 200) delay++;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x0E;
	GPIO_PORTF_DATA_R = (1<<3);
	while(1){
		GPIO_PORTF_DATA_R |= (1<<1);
	for(volatile unsigned int i = 0; i < 700000; i++) {}
		
	
		GPIO_PORTF_DATA_R &= ~(1<<1);
		for(volatile unsigned int i = 0; i < 700000; i++) {}
	}
}