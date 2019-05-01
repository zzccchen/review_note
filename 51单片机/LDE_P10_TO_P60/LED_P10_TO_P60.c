#include<uart.h>

#include<BoeBot.h>

int main()
{
	uart_Init();

	while (1)
	{
		P1_0 = P1_1 = P1_3 = P1_4 = P1_5 = P1_6 = 1;
		delay_nms(100);
		
		P1_0 = P1_1 = P1_3 = P1_4 = P1_5 = P1_6 = 0;
		delay_nms(100);
	}
}