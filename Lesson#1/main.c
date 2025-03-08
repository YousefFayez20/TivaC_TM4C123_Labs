static int counter = 0;

int main(void) {
   //0x40025000 -> PortF
	//0x400 -> GPIO Direction, 1-> output
	//0x51C -> Digital Enable
	//General-PurposeInput/OutputRunModeClockGatingControl (RCGCGPIO),offset0x60
	
	*((volatile unsigned int *)0x400FE608) =0x20;
	volatile unsigned int delay = 0;
    while(delay < 200) delay++;
	*((volatile unsigned int *)0x40025400) = 0x0E;
	*((volatile unsigned int *)0x4002551C) = 0x0E;
	
	while(1){
		*((volatile unsigned int *)0x400253FC) = 0x02;
	for(volatile unsigned int i = 0; i < 170000; i++) {}
		
	
		*((volatile unsigned int *)0x400253FC) = 0x00;
		for(volatile unsigned int i = 0; i < 170000; i++) {}
	}
}