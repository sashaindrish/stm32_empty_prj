#ifndef __HTU21_H
#define __HTU21_H
#include "stm32f10x.h"
#include "i2c.h"
#include "delayms.h"

#define HTU21DF_I2CADDR       0x40
#define HTU21DF_READTEMP      0xE3
#define HTU21DF_READHUM       0xE5
#define HTU21DF_WRITEREG       0xE6
#define HTU21DF_READREG       0xE7
#define HTU21DF_RESET       0xFE
#define boolean uint8_t

  boolean htu21_begin(void); // инициализация датчика 
  float readTemperature(void);// считать температуру 
  float readHumidity(void); // считать влажность  
  void reset(void);
  boolean readData(void);
	//float humidity, tempr;
extern I2C_InitTypeDef i2c;
#endif
