
  
//初始化PE8...PE15为输出口.并使能这八个口的时钟		    
//LED IO初始化

#include "sys.h"
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	                //使能PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|
                                  GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|
                                  GPIO_Pin_14|GPIO_Pin_15;				 	//LED1-->PE.8 ...  LED8-->PE.15 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			  	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 				//IO口速度为50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 				//根据设定参数初始化GPIOE
	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                 GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);			//PE.8 输出低
}

 
