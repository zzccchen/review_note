#include "hcrs04.h"
#include "delay.h"
#include "usart.h"
#include "hcrs04_timer.h"
#include "led.h"

extern u16 cnt;					//输出次数	 在timer.h中的cnt
extern u32 tim;					//接收定时器2的数据  在timer.h中的tim
float dis ;				        //距离

void HC_SR04_tInit(void)										
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;					
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		//PB12--ECHO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		//浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			//PB13--TRIG	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;					//模拟输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOB, GPIO_Pin_12 |GPIO_Pin_13);
	
	Tim2_Init(10, 71);
}
 
/*拉高TRIG也是PB13 15us*/
void SR04_Trg(void)										
{
	Trgger=1;
	delay_us(15);
	Trgger=0;
}

/*获取时间并计算距离*/
void SR04_Cnt(void)
{
	tim= TIM_GetCounter(TIM2);
	tim=tim+cnt*10;
	dis=tim*0.017;
	printf("\r\n超声距离：%.3f cm\r\n",dis);
	TIM2->CNT=0;											
	cnt=0; 
}

void hcrs04_running(void)
{

		SR04_Trg()	;
		while(ECHO == 0);
		TIM_Cmd(TIM2, ENABLE);
		while(ECHO == 1);
		TIM_Cmd(TIM2, DISABLE);
		SR04_Cnt();

}

