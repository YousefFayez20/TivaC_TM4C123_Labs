#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
	#include <string.h>
#include <stdlib.h>
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
void UART_init(){

}

void printChar( char c){
while((UART0_FR_R & (1<<5)) != 0 ){}
	UART0_DR_R = c;
}
void printString( char* string){
while (*string){
printChar(*(string++));
}
}


char readChar(){
	char x;
while((UART0_FR_R & (1<<4)) != 0 ){}
	x = UART0_DR_R;
	return x;
}

void TIMER0A_Handler()
{
	if(TIMER0_MIS_R&0x01){
	GPIO_PORTF_DATA_R ^= (1<<3);
	TIMER0_ICR_R |=0x1;
	}

}
char* readString(char delimiter)
{

  int stringSize = 0;
  char* string = (char*)calloc(10,sizeof(char));
  char c = readChar(); 
  printChar(c);
  
  while(c!=delimiter)
  { 

    *(string+stringSize) = c; // put the new character at the end of the array
    stringSize++;
    
    if((stringSize%10) == 0) // string length has reached multiple of 10
    {
      string = (char*)realloc(string,(stringSize+10)*sizeof(char)); // adjust string size by increasing size by another 10
    }
    
    c = readChar();
    printChar(c); // display the character the user typed
  }

  if(stringSize == 0)
  {
   
    return '\0'; // null car
  }
  return string;
}


int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	/* Set bit5 of RCGCGPIO to enable clock to PORTF*/
	SYSCTL_RCGCGPIO_R |= (1<<5) | (1<<0);
    while ((SYSCTL_PRGPIO_R & ((1<<5) | (1<<0))) == 0);

    SYSCTL_RCGCUART_R |= 0x01;
    while ((SYSCTL_PRUART_R & 0x01) == 0);
	//Alternate function for PA0, PA1
	GPIO_PORTA_AFSEL_R |= (1<<0) | (1<<1);
	
	//choose what function
	GPIO_PORTA_PCTL_R |= (1<<0) | (1<<4);
	GPIO_PORTA_DEN_R |= (1<<0) | (1<<1);
	
	
	// disable the UART by clearing the UARTEN bin
	UART0_CTL_R &= ~(1<<0);
	 // Find  the Baud-Rate Divisor
    // BRD = 16,000,000 / (16 * 9600) = 104.16666666666666666666666666666666666666666666666666
    // UARTFBRD[DIVFRAC] = integer(0.166667 * 64 + 0.5) = 11
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	
	// TheUARTLCRHregisteristhelinecontrolregister.Serialparameterssuchasdatalength,parity,
 //andstopbitselectionareimplementedinthisregister
	UART0_LCRH_R |= (3<<5) ;
	UART0_LCRH_R |= (1<<4);
	// 5. Configure the UART clock source by writing to the UARTCC register
	UART0_CC_R = 0x0;
	UART0_CTL_R |= (1<<0) |(1<<8) |(1<<9);
	 /* PORTF0 has special function, need to unlock to modify */
	
	// GPIOF LED setup
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x0E;
    GPIO_PORTF_PUR_R |= (1<<4) | (1<<0);




	
	
char c;
	while(1){
 printString("Enter \"r\", \"g\", or \"b\": \n\r" );
		c = readChar();
		printChar(c);
		printString("\n\r");
		
		switch(c){
			case 'r':
				GPIO_PORTF_DATA_R = (1<<1);
			  break;
			case 'b':
				GPIO_PORTF_DATA_R = (1<<2);
			  break;
			case 'g':
				GPIO_PORTF_DATA_R = (1<<3);
			  break;
			default:
				GPIO_PORTF_DATA_R &= ~((1<<2) | (1<<1) | (1<<3)) ;
			  break;
			
		}

	}
}