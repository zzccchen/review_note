#include< BoeBot.h>
#include<uart.h>

int P1_2state(void)
{
	return (P1&0x04)?1:0;
}
int P3_5state(void)
{
	return (P3&0x20)?1:0;
}
int main(void)
{
	int sp;
	int counter;
	uart_Init();
	printf("Program Running!\n");
		
	while(1)
	{
		for(counter=0;counter<38;counter++)
		{
			P1_4=1;
			P3_6=1;
    		delay_nus(13);
			P1_4=0;
			P3_6=0;  
    		delay_nus(13);
		 }
		irDetectLeft=P1_2state();
		irDetectRight=P3_5state();
		printf("irDetectLeft=%d\t",irDetectLeft);
		printf("irDetectRight=%d\n",irDetectRight);		
	}
}