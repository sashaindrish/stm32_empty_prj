#include "i2c.h"

void I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress)
{
  I2C_AcknowledgeConfig(I2Cx, ENABLE);  // ACK  ��������� ������ � �������� ������
	// �� ������ ������ ����, ���� ���� ������������
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
 
    // ���������� ����� - ��� ��� ������� )
    I2C_GenerateSTART(I2Cx, ENABLE);
 
    // ���� ���� ������� ������ ����
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)); // 
 
    // �������� ����� ������������
    I2C_Send7bitAddress(I2Cx, slaveAddress, transmissionDirection);
 
    // � ������ � ��� ��� �������� �������� ������� - � ����������� �� ���������� ����������� ������ �������
    if(transmissionDirection== I2C_Direction_Transmitter)
    {
    	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    }
 
    if(transmissionDirection== I2C_Direction_Receiver)
    {
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    }
}

/***************************************************************************************************/
void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data)
{
    // ������ �������� �������� ������� �� SPL � ����, ���� ������ ������
    I2C_SendData(I2Cx, data);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}
 
 
 
/***************************************************************************************************/
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx)
{
    uint8_t data;
    // ��� ������� ������, ��� ������ ������ ������ ���������� ��������� �� � ����������
    while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
    data = I2C_ReceiveData(I2Cx);
	  
    return data;
}

/***************************************************************************************************/
void I2C_StopTransmission(I2C_TypeDef* I2Cx){
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
		I2C_GenerateSTOP(I2Cx, ENABLE);
}
/***************************************************************************************************/

uint8_t I2C_Mem_Write(I2C_TypeDef* I2Cx,  uint8_t slaveAddress,uint8_t regAddres, uint8_t* pData, uint8_t length)
{
	uint8_t i=0;
	I2C_StartTransmission(I2Cx, I2C_Direction_Transmitter,  slaveAddress);
	I2C_WriteData(I2Cx,regAddres); 
	
	for(i=0;i<length;i++){
		I2C_WriteData(I2Cx, pData[i]);
	}
	I2C_StopTransmission(I2Cx);
	return 1;
}

uint8_t I2C_Mem_Read(I2C_TypeDef* I2Cx,  uint8_t slaveAddress,uint8_t regAddres, uint8_t* pData, uint8_t length)
{
	uint8_t i=0;
	I2C_StartTransmission(I2Cx, I2C_Direction_Transmitter,  slaveAddress);
	I2C_WriteData(I2Cx,regAddres);
	I2C_StopTransmission(I2Cx);
	
	for(uint16_t i=0;i<1000; i++); // delay
	
	I2C_StartTransmission(I2Cx, I2C_Direction_Receiver,  slaveAddress);
	
	for(i=0;i<length;i++){
		pData[i]=I2C_ReadData(I2Cx);
	}
	
	I2C_StopTransmission(I2Cx);
	return 1;
}

void send_data_ssd1306(I2C_TypeDef* I2Cx,  uint8_t slaveAddress, uint8_t* pData, uint8_t control_bit){
	uint8_t x;
	I2C_GenerateSTART(I2Cx, ENABLE);
	
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)){};
		
	I2C_Send7bitAddress(I2Cx, slaveAddress, I2C_Direction_Transmitter);	
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)){};
		
	I2C_SendData(I2Cx, control_bit);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){};
  
	for (x=0; x<8; x++)
	{
		I2C_SendData(I2Cx, pData[x]);
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){};
  }
	I2C_GenerateSTOP(I2Cx, ENABLE);
}

void ssd1306_I2C_WriteMulti( uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	uint8_t i;
	I2C_StartTransmission(I2C1, I2C_Direction_Transmitter,  address);
	 I2C_WriteData(I2C1, reg);
	for (i = 0; i < count; i++) {
		I2C_WriteData(I2C1, data[i]);
	}
	I2C_StopTransmission(I2C1);
}

