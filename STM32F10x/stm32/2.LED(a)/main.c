#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Init(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
}

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = 9000*nms;
	SysTick->VAL = 0X00;
	SysTick->CTRL = 0X01;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0X01)&&(!(temp&(1<<16))));
	SysTick->CTRL = 0X00;
	SysTick->VAL = 0X00;
}

void GPIO_Cfg(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

int main(void)
{	
	int flag = 0;
	int press = 0;
	Init();
	GPIO_Cfg();	

	while (1)
    {	
		if(press==0)
		{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==Bit_RESET)
			{
				delay_ms(10);
				flag=0;			
			}		
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==Bit_RESET)
			{
				delay_ms(10);
				flag=flag+1;
				if(flag==4)
					flag=1;
				press=1;
			}
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==Bit_SET && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==Bit_SET)
		{
			delay_ms(10);
			press=0;
		}
		if(flag==0)
		{	
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_14);	
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
		}
		else if(flag==1)
		{	
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_14);	
			GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		}
		else if(flag==2)
		{		
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		}
		else if(flag==3)
		{	
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);	
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		}
	}
}
