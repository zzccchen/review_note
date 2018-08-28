/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "led.h"
#include "usart.h"
#include "hcrs04.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern u8 RxBuffer[];
extern __IO uint8_t RxCounter;
extern u8 NbrOfDataToRead;
extern u8 bluetooth_data;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  外部中断线5~9的中断服务函数
  * @param  None
  * @retval None
  */
#if 0
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8) != RESET) //确保是否产生了EXTI Line中断
	{
		// LED0 取反
		LED1 = !LED1;
		EXTI_ClearITPendingBit(EXTI_Line8);     //清除中断标志位
	}
	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET) //确保是否产生了EXTI Line中断
	{
		// LED1 取反
		LED2 = !LED2;
		EXTI_ClearITPendingBit(EXTI_Line9);     //清除中断标志位
	}
}

#endif
/**
  * @brief  外部中断线10~15的中断服务函数
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET) //确保是否产生了EXTI Line中断
	{
		// LED0 取反
		LED3 = !LED3;
		EXTI_ClearITPendingBit(EXTI_Line10);     //清除中断标志位
	}
	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET) //确保是否产生了EXTI Line中断
	{
		// LED1 取反
		LED4 = !LED4;
		EXTI_ClearITPendingBit(EXTI_Line11);     //清除中断标志位
	}
}

/**
  * @brief  USART1中断服务程序
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	u8 Res;
  /*USART1接收中断*/
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		
		/* Read one byte from the receive data register */
		Res = USART_ReceiveData(USART1);
        //USART_SendData(USART2,Res);
		//Bluetooth_control(Res);
		USART_SendData(USART1, Res);
		
		//USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断标志位
		
		//bluetooth_data = 0;
  }

  /*USART1发送中断*/
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  { 
  }
}

/**
  * @brief  USART2中断服务程序
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
    /*USART2接收中断*/
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
       // usart2_res = USART_ReceiveData(USART2);
      
        //USART_SendData(USART1, usart2_res);
    }

    /*USART2发送中断*/
    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    { 
    }
}

/**
  * @brief  USART3中断服务程序
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
    /*USART3接收中断*/
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
    }

    /*USART3发送中断*/
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
    { 
    }
}

/**
  * @brief  定时器2的中断服务函数
  * @param  None
  * @retval None
*/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
