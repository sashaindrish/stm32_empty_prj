#ifndef __I2C_H
#define __I2C_H
#include "stm32f10x.h"
void I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress);
void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx);
void I2C_StopTransmission(I2C_TypeDef* I2Cx);
uint8_t I2C_Mem_Write(I2C_TypeDef* I2Cx,  uint8_t slaveAddress,uint8_t regAddres, uint8_t* pData, uint8_t length);
uint8_t I2C_Mem_Read(I2C_TypeDef* I2Cx,  uint8_t slaveAddress,uint8_t regAddres, uint8_t* pData, uint8_t length);
void send_data_ssd1306(I2C_TypeDef* I2Cx,  uint8_t slaveAddress, uint8_t* pData, uint8_t control_bit);
void ssd1306_I2C_WriteMulti( uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);
#endif
