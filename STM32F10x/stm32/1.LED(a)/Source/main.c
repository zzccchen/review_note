#include "stm32f10x_lib.h"
#include "sys.h"
	
/*------------------------------------------------------------
                           主函数
------------------------------------------------------------*/
int main()
{
    
    Stm32_Clock_Init();//系统时钟设置
	RCC->APB2ENR |= 0x00000001; //开启afio时钟
    AFIO->MAPR = (0x00FFFFFF & AFIO->MAPR)|0x04000000;          //关闭JTAG 
				

	RCC->APB2ENR|=0X0000001c;//先使能外设IO PORTa,b,c时钟
	
	GPIOB->CRH=0X33333333;    //推挽输出
	GPIOB->CRL=0X33333333;    //推挽输出
	GPIOC->CRH=0X33333333;    //推挽输出
	GPIOC->CRL=0X33333333;    //推挽输出
	GPIOA->CRH=0X33333333;    //推挽输出
	GPIOA->CRL=0X33333333;    //推挽输出

	 while (1)
    {			
	delay_ms(500);
	     	 
	GPIOB->ODR=0xffffffff;
	GPIOA->ODR=1;		
	GPIOC->ODR=0xffffffff;

	delay_ms(500);
	     	 
	GPIOB->ODR=0;
	GPIOA->ODR=0xffffffff;		
	GPIOC->ODR=0xffffffff;
	
	delay_ms(500);
	     	 
	GPIOB->ODR=0xffffffff;
	GPIOA->ODR=0xffffffff;		
	GPIOC->ODR=0;
	}
}
