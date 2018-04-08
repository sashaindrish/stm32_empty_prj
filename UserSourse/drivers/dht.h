#ifndef __DHT_H
#define __DHT_H
#include "stm32f10x.h"
#include "delayms.h"
//#define DHT22      
extern GPIO_InitTypeDef GPIO_InitStructure;

#define DHT_PORT        GPIOA
//#define DHT_DDR         GPIOC
//#define DHT_PIN         
#define DHT_PIN         GPIO_Pin_1
#define CORRE_TEMP			-2
#define CORRE_HUM				+10
void DHT_SetPinOUT(void);
void DHT_SetPinIN(void);
int read_dht_hum(void); 
uint8_t dht_read(float* h,float* t,int *p);

#endif

/*
	uint8_t temp[32]="";
	float hm=1,te=1;
	int p=1;

while(dht_read(&hm,&te,&p));
		sprintf((char*)temp,"h=%.1f t=%.1f p=%d\n",hm, te,p);
	HAL_UART_Transmit_IT(&huart1,temp,strlen((char*)temp));
*/
