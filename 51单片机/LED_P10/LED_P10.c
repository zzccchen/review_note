#include<uart.h>

#include<BoeBot.h>

int main()
{
	uart_Init();
	
	printf("The answer is:%d\n");
	while (1)
	{
		P1_0 =1;
		delay_nms(50);
		
		P1_0 = 0;
		delay_nms(50);
	}
}