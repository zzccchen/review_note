#include "hcrs04_timer.h"
#include "usart.h"
#include "delay.h"

#include "hcrs04.h"

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��2

u16 cnt;    //�����޶�������  ��hcrs04.h�пɼ�
u32 tim;		//��ʱʱ��    ��hcrs04.h�пɼ�

void Tim2_Init(u16 arr,u16 psc)	//arr���Զ���װֵ��	 psc��ʱ��Ԥ��Ƶ��
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc;  //72MHz/7200=10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ITConfig(TIM2,	TIM_IT_Update, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}

/*�жϷ�����򣺲�ѯ�жϱ�־λ�ж��Ƿ��ж�ʱ���жϡ�����жϹ���λ*/
void TIM2_IRQHandler(void)   //TIM2�жϷ����ӳ���
{
	/*���ָ����TIM�жϷ������:TIM �ж�Դ(ʵ���ϲ��ж�Ҳ�ǿ��Եģ�*/
	if (TIM_GetITStatus(TIM2, TIM_IT_Update ) != RESET)  
	{
		
		/*���TIMx���жϴ�����λ:TIM �ж�Դ */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
		cnt++;

		if(cnt == 2000)			//�����2000*10*0.00017=3.4m
		{
			cnt=0;
			tim=0;
			printf("\r\n��������Ӧ�����ࣩ\r\n");
			delay_ms(500);
		}
	}
}



