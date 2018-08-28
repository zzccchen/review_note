

#ifndef __USART_H
#define __USART_H

#include <stdio.h>
#include "sys.h"
typedef struct __va_list
{ void *__ap; } va_list;
#define va_start(ap, parmN) __va_start(ap, parmN)

#define va_arg(ap, type) __va_arg(ap, type)
enum CAR_DATA
{
	FORWARD = 0,
	BACKUP,
	TURNLEFT,
	TURNRIGHT,
	TURNSTOP,
	ADDSPEED,
	SUBSPEED
};

void USART1_Configuration(void);
void USART2_Configuration(void);
void USART3_Configuration(void);

void  Bluetooth_control(u8 control_data);	//��������С��

#endif
/******************* (C) ��Ȩ���� 2013 ̫ԭ�����Ƽ����޹�˾ *******************/
