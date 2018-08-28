#include "hcrs04_timer.h"
#include "usart.h"
#include "delay.h"

#include "hcrs04.h"

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器2

u16 cnt;    //计数限定最大距离  在hcrs04.h中可见
u32 tim;		//定时时间    在hcrs04.h中可见

void Tim2_Init(u16 arr,u16 psc)	//arr：自动重装值。	 psc：时钟预分频数
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc;  //72MHz/7200=10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM2,	TIM_IT_Update, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}

/*中断服务程序：查询中断标志位判断是否有定时器中断、清除中断挂起位*/
void TIM2_IRQHandler(void)   //TIM2中断服务子程序
{
	/*检查指定的TIM中断发生与否:TIM 中断源(实际上不判断也是可以的）*/
	if (TIM_GetITStatus(TIM2, TIM_IT_Update ) != RESET)  
	{
		
		/*清除TIMx的中断待处理位:TIM 中断源 */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
		cnt++;

		if(cnt == 2000)			//最大测距2000*10*0.00017=3.4m
		{
			cnt=0;
			tim=0;
			printf("\r\n超声无响应（超距）\r\n");
			delay_ms(500);
		}
	}
}



