#ifndef __MOTOR_28BYJ_48_H
#define __MOTOR_28BYJ_48_H
#include "stm32f10x.h"
#include "delayms.h"
#define port GPIOB
#define DELEY_M 980
extern GPIO_InitTypeDef GPIO_InitStructure;
void gpio_setup(uint16_t Pin_in1,uint16_t Pin_in2,uint16_t Pin_in3,uint16_t Pin_in4);
void set_step(uint32_t step);
void set_step_invert(uint32_t step_inv);


#endif
