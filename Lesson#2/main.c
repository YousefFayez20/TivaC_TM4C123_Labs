#include"TM4C123GH6PM.h""

int main(void) {
SYSCTL->RCGCGPIO |= 0x20; /*enable clock to gpiof*/
	GPIOF->LOCK = 0x4C4F434B; //unlock commit register
	GPIOF->CR = 0x01; /*make PORTF0 configurable*/
	
GPIOF->DIR |= 0x02; //PF1 output"led" SW2 on PF0 
GPIOF->DEN = 0xFF;
GPIOF->PUR = 0x01;
	unsigned int value;
	while(1){
	value = GPIOF->DATA;
		value =~value;
		value =value << 1;
		GPIOF->DATA = value;
		
	}
}