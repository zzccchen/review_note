#include "stm32f10x.h"
#include "sys.h"
	
/*------------------------------------------------------------
                           ������
------------------------------------------------------------*/
void delay_m(u16 nms)
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

int main()
{
    
    Stm32_Clock_Init();//ϵͳʱ������
	RCC->APB2ENR |= 0x00000001; //����afioʱ��
    AFIO->MAPR = (0x00FFFFFF & AFIO->MAPR)|0x04000000;          //�ر�JTAG 
				

	RCC->APB2ENR|=0X0000001c;//��ʹ������IO PORTa,b,cʱ��
	
	GPIOB->CRH=0X33333333;    //�������
	GPIOB->CRL=0X33333333;    //�������
	GPIOC->CRH=0X33333333;    //�������
	GPIOC->CRL=0X33333333;    //�������
	GPIOA->CRH=0X33333333;    //�������
	GPIOA->CRL=0X33333333;    //�������

	 while (1)
    {			
	delay_m(500);
	     	 
	GPIOB->ODR=0xffffffff;
	GPIOA->ODR=1;		
	GPIOC->ODR=0xffffffff;

	delay_m(500);
	     	 
	GPIOB->ODR=0;
	GPIOA->ODR=0xffffffff;		
	GPIOC->ODR=0xffffffff;
	
	delay_m(500);
	     	 
	GPIOB->ODR=0xffffffff;
	GPIOA->ODR=0xffffffff;		
	GPIOC->ODR=0;
	}
}
