#ifndef _BMP180_H_
#define _BMP180_H_

#include <math.h>
#include "stm32f10x.h"
#include "i2c.h"
#include "delayms.h"
///i2c def
#define hi2c1dev I2C1 
///
//#define BMP180_INCLUDE_INDIVIDUAL_CALIBRATION_ACCESS
#define BMP180_ADDRESS              0x77
#define BMP180_DEFAULT_ADDRESS      BMP180_ADDRESS
#define bool uint8_t

#define BMP180_RA_AC1_H     0xAA    /* AC1_H */
#define BMP180_RA_AC1_L     0xAB    /* AC1_L */
#define BMP180_RA_AC2_H     0xAC    /* AC2_H */
#define BMP180_RA_AC2_L     0xAD    /* AC2_L */
#define BMP180_RA_AC3_H     0xAE    /* AC3_H */
#define BMP180_RA_AC3_L     0xAF    /* AC3_L */
#define BMP180_RA_AC4_H     0xB0    /* AC4_H */
#define BMP180_RA_AC4_L     0xB1    /* AC4_L */
#define BMP180_RA_AC5_H     0xB2    /* AC5_H */
#define BMP180_RA_AC5_L     0xB3    /* AC5_L */
#define BMP180_RA_AC6_H     0xB4    /* AC6_H */
#define BMP180_RA_AC6_L     0xB5    /* AC6_L */
#define BMP180_RA_B1_H      0xB6    /* B1_H */
#define BMP180_RA_B1_L      0xB7    /* B1_L */
#define BMP180_RA_B2_H      0xB8    /* B2_H */
#define BMP180_RA_B2_L      0xB9    /* B2_L */
#define BMP180_RA_MB_H      0xBA    /* MB_H */
#define BMP180_RA_MB_L      0xBB    /* MB_L */
#define BMP180_RA_MC_H      0xBC    /* MC_H */
#define BMP180_RA_MC_L      0xBD    /* MC_L */
#define BMP180_RA_MD_H      0xBE    /* MD_H */
#define BMP180_RA_MD_L      0xBF    /* MD_L */
#define BMP180_RA_CONTROL   0xF4    /* CONTROL */
#define BMP180_RA_MSB       0xF6    /* MSB */
#define BMP180_RA_LSB       0xF7    /* LSB */
#define BMP180_RA_XLSB      0xF8    /* XLSB */

#define BMP180_MODE_TEMPERATURE     0x2E
#define BMP180_MODE_PRESSURE_0      0x34
#define BMP180_MODE_PRESSURE_1      0x74
#define BMP180_MODE_PRESSURE_2      0xB4
#define BMP180_MODE_PRESSURE_3      0xF4

void BMP180_initialize(void);
bool BMP180_testConnection(void);

/* calibration register methods */
int16_t     BMP180_getAC1(void);
int16_t     BMP180_getAC2(void);
int16_t     BMP180_getAC3(void);
uint16_t    BMP180_getAC4(void);
uint16_t    BMP180_getAC5(void);
uint16_t    BMP180_getAC6(void);
int16_t     BMP180_getB1(void);
int16_t     BMP180_getB2(void);
int16_t     BMP180_getMB(void);
int16_t     BMP180_getMC(void);
int16_t     BMP180_getMD(void);

/* CONTROL register methods */
uint8_t     BMP180_getControl(void);
void        BMP180_setControl(uint8_t value);

/* MEASURE register methods */
uint16_t    BMP180_getMeasurement2(void); // 16-bit data
uint32_t    BMP180_getMeasurement3(void); // 24-bit data
uint8_t     BMP180_getMeasureDelayMilliseconds(uint8_t mode);
uint16_t    BMP180_getMeasureDelayMicroseconds(uint8_t mode);

// convenience methods
void        BMP180_loadCalibration(void);
uint16_t    BMP180_getRawTemperature(void);
float       BMP180_getTemperatureC(void);
float       BMP180_getTemperatureF(void);
uint32_t    BMP180_getRawPressure(void);
float       BMP180_getPressure(uint8_t bmp180_mode);
float       BMP180_getAltitude(float pressure, float seaLevelPressure);

// i2c
uint8_t I2C_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout);
uint8_t I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout);
uint16_t I2C_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint16_t I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* pData);

#endif /* _BMP180_H_ */
