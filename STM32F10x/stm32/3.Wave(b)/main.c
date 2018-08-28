#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "main.h"
#include "stdio.h"

#include "string.h"
#include "stdlib.h"

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (u8)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}

void Init(void)
{
    SystemInit();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Cfg(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2); 
}

void TIM3_Cfg(void)
{

	u32 lx =99999; 
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStruct;

 	TIM_InitStructure.TIM_Period=7199;
   	TIM_InitStructure.TIM_Prescaler=999;
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3,&TIM_InitStructure);

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);

	TIM_Cmd(TIM3,ENABLE);

	
	TIM_InitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//APB1时钟1分频=36m
	TIM_InitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数器向下计数
	TIM_InitStructure.TIM_Period=lx;//1000;//1ms溢出一次
	TIM_InitStructure.TIM_Prescaler=719;//计数器时钟为1mhz
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure );

	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);

	TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
 }

void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = 9000 * nms;
    SysTick->VAL = 0X00;
    SysTick->CTRL = 0X01;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0X01) && (!(temp & (1 << 16))));
    SysTick->CTRL = 0X00;
    SysTick->VAL = 0X00;
}

void USART_Cfg(void)
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
}

void NVIC_Cfg(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

extern u32 rec_fre;
extern u32 rec_rat;
extern uint32_t Freq_InputCapture;
u32 rec_rat_=0;
u32 rec_fre_=0;
extern char p[20];
extern int i;
int main(void)
{
	
	char pt[25]="";
    Init();	
    GPIO_Cfg();
	TIM3_Cfg();
	
    NVIC_Cfg();
    USART_Cfg();

	TIM_SetCompare2(TIM3,5000);
	
    while (1)
    {
        
		// 更新设置
		if(strlen(p)!=0)
		{
			i=0;
			memset(pt,'\0',sizeof(pt));
			strcpy(pt,p);
			memset(p,'\0',sizeof(p));

			rec_fre_ = atoi(strtok(pt, "*"));		
			rec_rat_ = atoi(strtok(NULL, ","));
			
			if(rec_rat_>=0 && rec_rat_ <=100)
			{
				rec_fre = rec_fre_;
				rec_rat = rec_rat_;
				
				rec_fre=(72000/rec_fre)-1;		
				rec_rat=rec_rat*rec_fre/100;
				
				TIM_SetAutoreload(TIM3,rec_fre);
				TIM_SetCompare2(TIM3,rec_rat);		
	
				printf("\r\n更新设置成功...\r\n");
	
				printf("频率设置：%d Hz\t",rec_fre_);
		   		printf("占空比设置：%d %%\r\n",rec_rat_);
			}
			else
			{
				printf("\r\n更新设置失败\r\n占空比设置错误，错误值：%d %%...\r\n",rec_rat_);
			}
		}
		// 检测方波
		delay_ms(500);
		printf("当前频率：%d Hz\r\n",Freq_InputCapture);					
    }
}
