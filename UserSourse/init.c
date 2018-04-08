#include "init.h"
//#include "spi.h"
void delay_ms(uint32_t ms){
	
volatile uint32_t nCount; 
RCC_ClocksTypeDef RCC_Clocks; 
RCC_GetClocksFreq (&RCC_Clocks); 

nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms; 
for (; nCount!=0; nCount--); 
	
}

void init(){
	__enable_irq ();
	RCC_Configuration();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	 TIM_Cmd(TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure); GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 
    //ѕины PA9 и PA10 в режиме альтернативных функций Ц
    //Rx и Tx USARTТа
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		//// uart 
		USART_StructInit(&usart);
    usart.USART_BaudRate = BAUDRATE;
    USART_Init(USART1, &usart);
		//¬ключаем прерывани€ по приему байта и по окончанию передачи
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    USART_Cmd(USART1, ENABLE);
		//init_I2C1();
	//	spiinit();
    
}

void init_I2C1(uint16_t I2CMode)
{
	I2C_DeInit(I2C1); // сброс настроек I2C
		
	//I2C_Cmd(I2C1, DISABLE); //init_I2C1(I2C_Mode_SMBusHost); // режим SMBusHost или  I2C_Mode_I2C
	
			for(uint16_t i=0;i<1000; i++){
			} // delay
			
    // ¬ключаем тактирование нужных модулей
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 
    // ј вот и настройка I2C
    i2c.I2C_ClockSpeed = 100000; 
    i2c.I2C_Mode = I2CMode;//I2C_Mode_I2C; I2C_Mode_SMBusHost
		
    i2c.I2C_DutyCycle = I2C_DutyCycle_2;
    // јдрес € тут вз€л первый пришедший в голову 
   //i2c.I2C_OwnAddress1 = 0x00;
    i2c.I2C_Ack = I2C_Ack_Enable;
    i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &i2c);
 
    // I2C использует две ноги микроконтроллера, их тоже нужно настроить
		GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;// pb6- scl pb7- sda
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;			
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
 
    //GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_InitStructure);
    //GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_InitStructure);
 
    // Ќу и включаем, собственно, модуль I2C1
    I2C_Cmd(I2C1, ENABLE);
		
}
 

void RCC_Configuration(void)
{
    /*RCC system reset(for debug purpose) */
    RCC_DeInit();
    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);
    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS)
    {
        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        /* PCLK2 = HCLK*/
        RCC_PCLK2Config(RCC_HCLK_Div1);
        /* PCLK1 = HCLK*/
        RCC_PCLK1Config(RCC_HCLK_Div1);
        //ADC CLK
        RCC_ADCCLKConfig(RCC_PCLK2_Div2);
        /* PLLCLK = 8MHz * 3 = 24 MHz */
        RCC_PLLConfig(((uint32_t)0x00010000) , RCC_PLLMul_3);
        /* Enable PLL */
        RCC_PLLCmd(ENABLE);
        /* Wait till PLL is ready */
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        /* Wait till PLL is used as system clock source */
        while (RCC_GetSYSCLKSource() != 0x08) {}
    }
}

void init_gpio_out(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE );
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	
}

