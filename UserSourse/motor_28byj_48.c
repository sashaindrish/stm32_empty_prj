#include "motor_28byj_48.h"
uint16_t in1,in2,in3,in4;
GPIO_TypeDef PORT_in;
void gpio_setup(uint16_t Pin_in1,uint16_t Pin_in2,uint16_t Pin_in3,uint16_t Pin_in4)
{
	//PORT_in =PORT;
	in1 = Pin_in1;
	in2 = Pin_in2;
	in3 = Pin_in3;
	in4 = Pin_in4;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
  GPIO_InitStructure.GPIO_Pin = Pin_in1| Pin_in2|Pin_in3|Pin_in4;//GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(port, &GPIO_InitStructure); 
	
}

void set_step(uint32_t step){
	//GPIO_ResetBits(port,in1|in2|in3|in4);
	_delay_ms(5);
	for(uint32_t i=0;i<=step/4;i++){
			delay_us(DELEY_M);
	GPIO_SetBits(port,in1);
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in1);
		GPIO_SetBits(port,in2);
				delay_us(DELEY_M);
	GPIO_SetBits(port,in2);
		
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in2);
		GPIO_SetBits(port,in3);
				delay_us(DELEY_M);
	GPIO_SetBits(port,in3);
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in3);
		GPIO_SetBits(port,in4);
						delay_us(DELEY_M);
	GPIO_SetBits(port,in4);
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in4);
	GPIO_SetBits(port,in1);
	}
	GPIO_ResetBits(port,in1|in2|in3|in4);
	
}

void set_step_invert(uint32_t step_inv){
	//GPIO_ResetBits(port,in1|in2|in3|in4);
	_delay_ms(5);
	for(uint32_t i=0;i<=step_inv/4;i++){
			delay_us(DELEY_M);
	GPIO_SetBits(port,in4);
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in4);
		GPIO_SetBits(port,in3);
				delay_us(DELEY_M);
	GPIO_SetBits(port,in3);
		
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in3);
		GPIO_SetBits(port,in2);
				delay_us(DELEY_M);
	GPIO_SetBits(port,in2);
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in2);
		GPIO_SetBits(port,in1);
						delay_us(DELEY_M);
	GPIO_SetBits(port,in1);
		delay_us(DELEY_M);
	GPIO_ResetBits(port,in1);
	GPIO_SetBits(port,in4);
	}
	GPIO_ResetBits(port,in1|in2|in3|in4);
}

