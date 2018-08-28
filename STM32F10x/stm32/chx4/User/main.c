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

	USART1_Configuration();         //串口1初始化	
	  USARTx_NVIC_Configuration();
	 delay_init();
	 KEY_Init();
	
    USART1_Configuration();         //串口1初始化	
    USARTx_NVIC_Configuration();
	HC_SR04_tInit();                //超声波初始化
    
	   
 while(1)
 {
 		hcrs04_running();              //超声波测距
	   if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8))
			printf("红外信号丢失\r\n");
		else
		    printf("红外信号正常\r\n");
		delay_ms(1000);
 }
}


