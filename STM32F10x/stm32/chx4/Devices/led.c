
  
//��ʼ��PE8...PE15Ϊ�����.��ʹ����˸��ڵ�ʱ��		    
//LED IO��ʼ��

#include "sys.h"
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	                //ʹ��PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|
                                  GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|
                                  GPIO_Pin_14|GPIO_Pin_15;				 	//LED1-->PE.8 ...  LED8-->PE.15 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 			  	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 				//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOE, &GPIO_InitStructure);					 				//�����趨������ʼ��GPIOE
	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|
                 GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);			//PE.8 �����
}

 
