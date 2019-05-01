#include<BoeBot.h>
#include<uart.h>

int L_zero=1539;
int R_zero=1520;

int L_speed_us(int ls)
{
	if(ls<-200) return 1339;
	else if(ls>200) return 1739;
	else return L_zero+ls;
}

int R_speed_us(int rs)
{
	if(rs<-200) return 1720;
	else if(rs>200) return 1320;
	else return R_zero-rs;
}

int main()
{
	int sp,time_l,time_c;
	uart_Init();
	for(sp=20;sp<=200;sp+=20)
	{		
		P1_0=1;
		delay_nus(L_speed_us(sp));
		P1_0=0;
		
		P1_1=1;
		delay_nus(R_speed_us(sp));			
		P1_1=0;
			
		delay_nms(20);
	}
	while(1)
	{
		for(time_l=0;time_l<10;time_l++)
		{
			P1_0=1;
			delay_nus(L_speed_us(200));
			P1_0=0;
			
			P1_1=1;
			delay_nus(R_speed_us(200));			
			P1_1=0;
			
			delay_nms(20);
		}
		for(time_c=0;time_c<46;time_c++)
		{
			P1_0=1;
			delay_nus(L_speed_us(20));
			P1_0=0;
			
			P1_1=1;
			delay_nus(R_speed_us(200));			
			P1_1=0;
			
			delay_nms(20);
		}
	}
}