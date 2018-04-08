#include "delayms.h"

void delay_us(uint16_t time){
		TIM3->PSC = (F_TIMER/1000000)-1;             
    TIM3->ARR = time;                      
    TIM3->EGR = TIM_EGR_UG;                 
    TIM3->CR1 = TIM_CR1_CEN|TIM_CR1_OPM;    
    while ((TIM3->CR1 & TIM_CR1_CEN)!=0); 
	
}

void _delay_ms (uint16_t delay)
{
    TIM3->PSC = (F_TIMER/1000)-1;             
    TIM3->ARR = delay;                      
    TIM3->EGR = TIM_EGR_UG;                 
    TIM3->CR1 = TIM_CR1_CEN|TIM_CR1_OPM;    
    while ((TIM3->CR1 & TIM_CR1_CEN)!=0);   
}
