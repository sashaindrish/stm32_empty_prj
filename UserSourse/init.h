#ifndef __INIT_H
#define __INIT_H
#include "stm32f10x.h"
#define BAUDRATE 9600
void delay_ms(uint32_t ms);
void RCC_Configuration(void);
void init(void);
void init_I2C1(uint16_t I2CMode);
void init_gpio_out(void);

extern ErrorStatus HSEStartUpStatus;
extern GPIO_InitTypeDef GPIO_InitStructure;
extern RCC_ClocksTypeDef RCC_Clocks;
extern USART_InitTypeDef usart;
extern I2C_InitTypeDef i2c;
#endif
