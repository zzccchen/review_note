#ifndef __HCSR04_H_
#define __HCSR04_H_	 
#include "stm32f10x.h"

#define Trgger PBout(13)
#define ECHO PBin(12)

void HC_SR04_tInit(void);

void SR04_Trg(void);
void SR04_Cnt(void);

void hcrs04_running(void);
		 				    
#endif   //__HCSR04_H_
