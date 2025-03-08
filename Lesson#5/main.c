#define RCGCGPIO *((volatile unsigned int *)0x400FE608)
#define GPIOF_BASE 0x40025000
#define GPIOF_DIR  (*((volatile unsigned int *)(GPIOF_BASE + 0x400)))
#define GPIOF_DEN  (*((volatile unsigned int *)(GPIOF_BASE + 0x51C)))
#define GPIOF_DATA  (*((volatile unsigned int *)(GPIOF_BASE + 0x3FC)))
int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	RCGCGPIO =0x20;
	volatile unsigned int delay = 0;
    while(delay < 200) delay++;
	GPIOF_DIR = 0x0E;
	GPIOF_DEN = 0x0E;
	
	while(1){
		GPIOF_DATA = 0x02;
	for(volatile unsigned int i = 0; i < 170000; i++) {}
		
	
		GPIOF_DATA = 0x00;
		for(volatile unsigned int i = 0; i < 170000; i++) {}
	}
}