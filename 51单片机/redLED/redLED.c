#include< BoeBot.h>
#include<uart.h>
int L_zero=1480;
int R_zero=1440;

int L_speed_us(int ls)
{
	if(ls<-200) return L_zero-200;
	else if(ls>200) return L_zero+200;
	else return L_zero+ls;
}

int R_speed_us(int rs)
{
	if(rs<-200) return R_zero+200;
	else if(rs>200) return R_zero-200;
	else return R_zero-rs;
}
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
	int irDetectLeft;
	int irDetectRight;
	uart_Init();
	printf("Program Running!\n");
	

		
		/*for(sp=200;sp>=0;sp-=200)
		{	
		P1_0=1;
			delay_nus(L_speed_us(sp));
			P1_0=0;
			
			P1_1=1;
			delay_nus(R_speed_us(sp));			
			P1_1=0;
			
			delay_nms(20);	
		}*/
		
	
		delay_nms(20);
		//delay_nms(10000);
while(1)
	{
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
		/*for(counter=0;counter<38;counter++)
		{
			P1_4=1;
			P3_6=1;
      delay_nus(13);
			P1_4=0;
			P3_6=0;  
      delay_nus(13);
		 }*/
		irDetectLeft=P1_2state();
		irDetectRight=P3_5state();
		//printf("irDetectLeft=%d\t",irDetectLeft);
		//printf("irDetectRight=%d\n",irDetectRight);
		P1_0=1;
			delay_nus(L_speed_us(0));
			P1_0=0;
			
			P1_1=1;
			delay_nus(R_speed_us(0));			
			P1_1=0;
			
			delay_nms(20);
		if(1)
		{
			P1_0=1;
			delay_nus(L_speed_us(0));
			P1_0=0;
			
			P1_1=1;
			delay_nus(R_speed_us(0));			
			P1_1=0;
			
			delay_nms(20);
		}
		else
		{
			P1_0=1;
			delay_nus(L_speed_us(0));
			P1_0=0;
			
			P1_1=1;
			delay_nus(R_speed_us(0));			
			P1_1=0;
			
			delay_nms(20);
		}
		//delay_nms(100);
	}
}