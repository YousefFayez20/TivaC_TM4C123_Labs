#include"TM4C123GH6PM.h"
volatile int counter = 0;
int main(void) {
int *p_int;
	p_int = &counter;
	
	while(*p_int < 21){
++(*p_int);
	}
}