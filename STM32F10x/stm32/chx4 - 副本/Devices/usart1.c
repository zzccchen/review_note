 
	
#include "usart.h"
#include "stm32f10x.h"
#include <stdio.h>


/**
  * @brief  USARTxʱ�ӳ�ʼ������
  * @param  None
  * @retval None
  */
static void USART1_RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | 
		RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  USART��GPIO��ʼ������
  * @param  None
  * @retval None
  */
static void USART1_GPIO_Configuration(void)
{
    /*����GPIO��ʼ���ṹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    /*��ʼ���ṹ��*/
    GPIO_StructInit(&GPIO_InitStructure);    
     
    /*����USART1�Ľ��ն˿�*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA.10
   
    /*����USART1�ķ��Ͷ˿�*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������    
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA.9
}

/**
  * @brief  USART1���ڳ�ʼ������
  * @param  None
  * @retval None
  */
void USART1_Configuration()
{
    USART_InitTypeDef USART_InitStructure;

    /*USART���ʱ�ӳ�ʼ������*/
    USART1_RCC_Configuration();

    /*USART���GPIO��ʼ������*/
    USART1_GPIO_Configuration();

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /*����USART1���첽˫�����й���ģʽ*/
    USART_Init(USART1, &USART_InitStructure);

    /*ʹ��USART1�Ľ����ж� */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /*�ر�USART1�ķ����ж�*/
    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);

    /*ʹ��USART1*/
    USART_Cmd(USART1, ENABLE);
}
#if 1
/**
  * @brief  �ض���C�����е�printf������USART
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (u8)ch);

  /* ѭ��ֱ�����ͽ��� */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  }
  return ch;
}
#endif

