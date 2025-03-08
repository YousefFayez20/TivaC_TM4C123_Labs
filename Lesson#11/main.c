#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
	
#include "tm4c123gh6pm.h"


void TIMER0_Oneshot_init(int seconds){
	//Clock of TIMER0 must be enabled
	SYSCTL_RCGCTIMER_R |= 0x01;
	//disable timer before initialization
	TIMER0_CTL_R = 0;
	
TIMER0_CFG_R = 0x00;
TIMER0_TAMR_R |= 0x01;
	TIMER0_TAILR_R = (16000000*seconds-1);
	TIMER0_ICR_R |=0x1;
	TIMER0_CTL_R |= 0x01;
	while((TIMER0_RIS_R & 0x1) == 0){}

}
//wait for timeout multiple times, the overhead time of setting up the timer
//for oneshot mode will accumulate and causes inaccuracy
void TIMER0_PERIODIC_init(int seconds){
	//Clock of TIMER0 must be enabled
	SYSCTL_RCGCTIMER_R |= 0x01;
	//disable timer before initialization
	TIMER0_CTL_R = 0;
	
TIMER0_CFG_R = 0x04;
TIMER0_TAMR_R |= 0x02;
	TIMER0_TAILR_R = (62745-1); //load the value when counting down
	TIMER0_TAPR_R = 254 - 1;
	TIMER0_ICR_R |=0x1;
	TIMER0_CTL_R |= 0x01;
	int i =0;
	for(i = 0; i<seconds;i++)
	{
	while((TIMER0_RIS_R & 0x1) == 0){}
		TIMER0_ICR_R |=0x1;
	}

}

void SysTick_Handler(){
	
GPIO_PORTF_DATA_R ^= (1<<1);
}
int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	RCGCGPIO |= 0x20;
	while ((SYSCTL_PRGPIO_R & 0x20) == 0);
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x0E;
	//GPIO_PORTF_DATA_R = (1<<3);
	NVIC_ST_RELOAD_R = 16000000 - 1;
	NVIC_ST_CTRL_R |= 7;
	
	__asm(" CPSIE I");
	
	

	while(1){
		
		
		/*
					GPIO_PORTF_DATA_R |= (1<<1);
			TIMER0_PERIODIC_init(30);
		GPIO_PORTF_DATA_R &= ~(1<<1);
		TIMER0_PERIODIC_init(5);
		*/
	}
}