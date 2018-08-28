#include "stm32f10x_lib.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Init(void)
{
	SystemInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALL,ENABLE);
}

void GPIO_Cfg(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

int main(void)
{	
	Init();
	GPIO_Cfg();	

	while (1)
    {			
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	}
}
