#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
	
#include "tm4c123gh6pm.h"

void systick_init(void){
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_RELOAD_R = 16000000-1;
	NVIC_ST_CTRL_R |= 0x01;
	NVIC_ST_CTRL_R |= (1<<2);
	//STRELOAD

}
int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	RCGCGPIO |= 0x20;
	systick_init();
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x0E;
	GPIO_PORTF_DATA_R = (1<<3);
	volatile int x = 0;
	while(1){
		
	
		if(NVIC_ST_CTRL_R & (1<<16)){
			++x;
		GPIO_PORTF_DATA_R ^= (1<<1);
			if(x %2 == 0){
			GPIO_PORTF_DATA_R ^= (1<<2);
			}
				if(x %4 == 0){
			GPIO_PORTF_DATA_R ^= (1<<3);
					x = 0;
			}
		}
		

		
	


	}
}