#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"

#include "htu21.h"
#include "init.h"
#include "delayms.h"
#include "motor_28byj_48.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "main.h"



GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;
RCC_ClocksTypeDef RCC_Clocks;
USART_InitTypeDef usart;
I2C_InitTypeDef i2c;
SPI_InitTypeDef SPI_InitStructure;

void printstr(char  str[]);
void NVIC_Configuration(void);
void send_data_uart(uint8_t data);
void ADC_DMA_init(void);
void go_home_m(void);
void go_end_m(void);
void set_measure(void);


uint8_t usartDataTx[64]="hello_world",usartTx=0,flagTx=1;
uint8_t usartDataRx[256];
uint8_t countRx=0,countTx=0,countRx_C=0,countRx_R=0;
char temp[20]="0";
volatile uint16_t ADCBuffer[] = {0xAAAA, 0xAAAA}; // ����� ��� adc  ���� ������ ������ 
volatile short FLAG_ECHO = 0;
 uint8_t buffer[64] = {'\0'};


//������� ���������� ����
uint16_t usartCounter = 0;

    


int main()
{

	
	
	init();
	NVIC_Configuration();

	//init_gpio_out(); 
	gpio_setup(GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15);
	RCC_ADCCLKConfig (RCC_PCLK2_Div2); // 12mhz
	ADC_DMA_init();
	init_I2C1(I2C_Mode_SMBusHost);
	//readHumidity();
//	readTemperature();
	delay_ms(100);
	printstr("hello\n\r");
	delay_ms(200);
	printstr("Ok go home\n\r");
	delay_ms(100);
	go_home_m();
	delay_ms(100);
	printstr("home\n\r");
	delay_ms(100);
	
		
	while(1){
	
			
		
		
	}
	
 }
 
 //////////////////////////////////////////////////////////// usart
void printstr(char  str[]){
	uint8_t j=0;
	while(usartDataTx[j]){ // ������� ������ ����� �������
		usartDataTx[j]=0;
		j++;
		if(j==64){	
			j=0;
		}
		
	}
	j=0;
	while(str[j]){ // ������ ������ ��� �������� � �����
		usartDataTx[j]=(uint8_t)str[j];
		j++;
		if(j==64){	
			j=0;
		}
		
	}
	USART_SendData(USART1,usartDataTx[countTx]); // �������� ������� ������� 
		countTx++; // ���������� �������� �� 1 
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); // ���������� ��������� �� ���������� ��������
	
}
//////////////////////////////////////////////////////////
void send_data_uart(uint8_t data){
		//_delay_ms(1);
	//while(!(USART1->SR & USART_SR_TC)) {} // & USART_GetITStatus(USART1, USART_IT_TXE) !
   // USART_SendData(USART1,data);
		
	
}

///////////////////////////////////////////////////////// ������ ���������� usart 

void USART1_IRQHandler()
{
    if (USART_GetITStatus(USART1, USART_IT_TXE) ==SET )// ��������� �� �������� �������� ����� �� ���������� transmit
    {	
			USART_ClearITPendingBit(USART1, USART_IT_TXE); // ����� ����� USART_IT_TXE
			if(usartDataTx[countTx]!=0){ // �������� �� ������� �������� ��� ��������
				USART_SendData(USART1,usartDataTx[countTx]);// �������� ������
				countTx++;// ����������� ������� �� 1
			}else{ // ���� ������ ����������� ��
				countTx=0; // ������� ��������� �� 0 
				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);// ��������� ���� �������� �������
			}
			
    }
    
	//���������, ������������� �� ���������� ������� ������� ������ �����
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    {	
			USART_ClearITPendingBit(USART1, USART_IT_RXNE); // �������� ���� ����� ������ ������� 
		usartDataRx[countRx] = USART_ReceiveData(USART1); // ������� ������ � �������� � ������ �����
		//USART_SendData(USART1,usartDataRx[countRx]);
		countRx++; //  ��������� ������� ����� �� 1 
		countRx_C++; // ��������� ������� �� 1 
			
			//countRx=0;
		
    }
}
 
///////////////////////////////////////////////////////////////////////////////// ���������� 
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; // ���������� ��������� ���������� 

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);// ������ ���������� 0
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // ����� ��������� �����
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // ��������� ��������� 0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //  ������� �������� 
  NVIC_Init(&NVIC_InitStructure);// ��������� ��������� ���������� 

}


 
void ADC_DMA_init(void) // ������������� dma � adc 
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
 
    RCC_ADCCLKConfig(RCC_PCLK2_Div2);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE );
 
    DMA_InitStructure.DMA_BufferSize = 2;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADCBuffer;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1 , ENABLE ) ;
		// gpio init
 ///////////////////////////////////////////////////////////////////////////////////
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;//|GPIO_Pin_3 | GPIO_Pin_4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		// adc init 
 ///////////////////////////////////////////////////////////////////////////////////
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_NbrOfChannel = 2;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_7Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_7Cycles5);

    ADC_Cmd(ADC1 , ENABLE ) ;
    ADC_DMACmd(ADC1 , ENABLE ) ;
    ADC_ResetCalibration(ADC1);
 
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
 
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd ( ADC1 , ENABLE ) ;
}
///////////////////////////////////////////////////////////////////////////////////////

void go_home_m(void){
	while(ADCBuffer[0]<=2500){
		set_step(32);
	}
}
////////////////////////////////////////////////////////////////////////////////////////
void go_end_m(void){
		while(ADCBuffer[1]<=2500){
		set_step_invert(32);
	}
}

void set_measure(void){
	char temp2[16];
	
	go_end_m();
	delay_ms(1000);
	sprintf(temp2,"T=%.1f*\n\r",readTemperature());
	printstr(temp2);
	memset(temp2,0,16);
	sprintf(temp2,"H=%.1f%%\n\r",readHumidity());
	printstr(temp2);
	delay_ms(1000);
	go_home_m();
	
}


