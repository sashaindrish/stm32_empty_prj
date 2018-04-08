#ifndef __DELAYMS_H
#define __DELAYMS_H
#include "stm32f10x.h"
#define F_TIMER 24000000

void delay_us(uint16_t time);

void _delay_ms (uint16_t delay);

#endif
