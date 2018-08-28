/**
  ******************************************************************************
  * @file    main.c
  */  
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "hcrs04.h"
#include <stdio.h>
#include "hcrs04.h"


#define RxBufferSize 100
u8 RxBuffer[RxBufferSize];
__IO uint8_t RxCounter = 0x00;
u8 NbrOfDataToRead = RxBufferSize;


void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}

int main(void)
{
	delay_init();

	USART1_Configuration();         //����1��ʼ��	
	  USARTx_NVIC_Configuration();
	 delay_init();
	 KEY_Init();
	
    USART1_Configuration();         //����1��ʼ��	
    USARTx_NVIC_Configuration();
	HC_SR04_tInit();                //��������ʼ��
    
	   
 while(1)
 {
 		hcrs04_running();              //���������
	   if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8))
			printf("�����źŶ�ʧ\r\n");
		else
		    printf("�����ź�����\r\n");
		delay_ms(1000);
 }
}


