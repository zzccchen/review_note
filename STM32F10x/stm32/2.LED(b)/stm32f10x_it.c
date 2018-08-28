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


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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

extern int flag = 0;

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = 9000*nms;
	SysTick->VAL = 0X00;
	SysTick->CTRL = 0X01;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0X01)&&(!(temp&(1<<16))));
	SysTick->CTRL = 0X00;
	SysTick->VAL = 0X00;
}

void EXTI1_IRQHandler(void)
{
	static int press = 1;
	if(EXTI_GetITStatus(EXTI_Line1)==SET& press == 0)
	{
		flag=flag+1;
		if(flag==4)
			flag=1;
		press=1;
		
		if(flag==0)
		{	
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_14);	
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
		}
		else if(flag==1)
		{	
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_14);	
			GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		}
		else if(flag==2)
		{		
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		}
		else if(flag==3)
		{	
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);	
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		}
		delay_ms(80);
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
	else
	{
		delay_ms(100);
		press=0;
	}

}

void EXTI2_IRQHandler(void)
{
	static int press = 0;
	if(EXTI_GetITStatus(EXTI_Line2)==SET& press == 0)
	{
		press=1;
		flag=0;	
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);	
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		delay_ms(80);
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
	else
	{
		delay_ms(100);
		press=0;
	}

}

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
