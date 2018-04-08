#include "dht.h"

uint8_t data[5]={0,0,0,0,0};
#ifdef DHT22
 float h1=0;
 float t1=0;
#endif
 uint8_t hum=0;

void DHT_SetPinOUT(void) {
	
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=DHT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//GPIO_MODE_OUTPUT_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DHT_PORT,&GPIO_InitStructure);
	GPIO_SetBits(DHT_PORT,DHT_PIN);
}

void DHT_SetPinIN(void) {
GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=DHT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(DHT_PORT,&GPIO_InitStructure);

}


int read_dht_hum(void)   
{

	uint8_t i,j;

	//=============MCU send START
	DHT_SetPinOUT(); //pin as output
	GPIO_WriteBit(DHT_PORT, DHT_PIN, Bit_RESET); //0
	_delay_ms(19);
	GPIO_WriteBit(DHT_PORT, DHT_PIN, Bit_SET); //1
	DHT_SetPinIN(); //pin as input
	//=============check DHT11 response
	delay_us(50);
	if (GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN))
			{
			return 0;
			}
	delay_us(80);
	if (!(GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN)))
			{
			return 0;
			}
	//===============receive 40 data bits
	while (GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN));
	for (j=0; j<5; j++)
			{
			data[j]=0;
			for(i=0; i<8; i++)
					{
					while (!(GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN)));
					delay_us (30);
					if (GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN))
							data[j]|=1<<(7-i);
					while (GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN));
					}
			}

	return 1; 
	//DHT11 data[0]-humidity, data[2]-temperature 
	//DHT22 data[0]-data[1]-humidity, data[2]-data[3]-temperature
}

uint8_t dht_read(float* h,float* t,int *p)
{
   hum=0;
       //
        hum = read_dht_hum();
       //
    if(hum==1)
    { 
      #ifdef DHT22
     h1 = (float) data[0] * 256 + data[1];
     *h = h1/10.0;
     t1 = (float) data[2] * 256 + data[3];
     *t = t1/10.0;  
     #else
     *h =  data[0] CORRE_HUM;
     *t =  data[2] CORRE_TEMP;
			*p = data[4] CORRE_HUM CORRE_TEMP;
			
     #endif
     }else{
		 *h =  -1;
     *t =  -1;
		 }
		 return (data[2]+data[0])&~data[4];
}

