#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
	
#include "tm4c123gh6pm.h"


//wait for timeout multiple times, the overhead time of setting up the timer
//for oneshot mode will accumulate and causes inaccuracy
void TIMER0_PERIODIC_init(int seconds){
	//Clock of TIMER0 must be enabled
	SYSCTL_RCGCTIMER_R |= 0x01;
	//disable timer before initialization
	TIMER0_CTL_R = 0;
	
TIMER0_CFG_R = 0x04;
TIMER0_TAMR_R |= 0x02;
	TIMER0_TAPR_R = 250 - 1;
	TIMER0_TAILR_R = ((64000)-1); //load the value when counting down
	TIMER0_ICR_R |=0x1;
	TIMER0_IMR_R |=0x01;
		TIMER0_ICR_R |=0x1;
	TIMER0_CTL_R |= 0x01;
	//timer ->19
	NVIC_EN0_R |= (1<<19);
	


}
void TIMER0A_Handler()
{
	if(TIMER0_MIS_R&0x01){
	GPIO_PORTF_DATA_R ^= (1<<3);
	TIMER0_ICR_R |=0x1;
	}

}


int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	/* Set bit5 of RCGCGPIO to enable clock to PORTF*/
	RCGCGPIO |= 0x20;
	while ((SYSCTL_PRGPIO_R & 0x20) == 0);
	 /* PORTF0 has special function, need to unlock to modify */
	
	 /*Initialize PF3 as a digital output, PF0 and PF4 as digital input pins */
	GPIO_PORTF_LOCK_R = 0x4C4F434B; 
GPIO_PORTF_CR_R = 0x01;
GPIO_PORTF_LOCK_R =0;	
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R = 0x0E;
	//GPIO_PORTF_DATA_R = (1<<3);
//PORTF4,0 input pins
	GPIO_PORTF_DIR_R &= ~((1<<0) | (1<<4));
	GPIO_PORTF_DEN_R |=((1<<0) | (1<<4)) ;
	GPIO_PORTF_PUR_R |=(1<<4) | (1<<0);
TIMER0_PERIODIC_init(5);


	__asm(" CPSIE I");
	
	

	while(1){
		__asm(" wfi ");
		

	}
}