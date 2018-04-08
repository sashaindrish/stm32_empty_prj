#include "bmp180.h"


static uint8_t devAddr = BMP180_DEFAULT_ADDRESS;
static uint8_t buffer[3];

//static bool calibrationLoaded;
static int16_t ac1, ac2, ac3, b1, b2, mc, md;
static int16_t mb,calibrationLoaded = 1;;
static uint16_t ac4, ac5, ac6;
static int32_t b5;
static uint8_t measureMode;

/**
 * Specific address constructor.
 * @param address Specific device address
 * @see BMP180_DEFAULT_ADDRESS
 */
 
 uint16_t I2C_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
    return I2C_writeBytes(devAddr, regAddr, 1, &data);
}

uint16_t I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* pData)
{
    
    return I2C_Mem_Write(hi2c1dev, devAddr << 1, regAddr, pData, length);//
}

 uint8_t I2C_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout)
{
	/**
 * devAddr - адрес устройства
	* regAddr - адрес регистра
	1- количество бит
	data -  получаемые данные
 * timeout - задержка
 */
    return I2C_readBytes(devAddr, regAddr, 1, data, timeout);
}
 
 uint8_t I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout)
{
//HAL_I2C_Master_Transmit(&hi2c1dev, devAddr << 1, &regAddr, 1,timeout);
		 //if (HAL_I2C_Mem_Read(&hi2c1dev, (uint16_t)devAddr << 1,regAddr, I2C_MEMADD_SIZE_8BIT, data, length,timeout)== HAL_OK) return length; // чтение переданного регистра и следующих , timeout
   // return 0;
    
    return I2C_Mem_Read(hi2c1dev,  devAddr << 1,regAddr, data, length);
}
 
void BMP180_setAddress(uint8_t address) // установа адреса 
{
    devAddr = address;
}

/**
 * Prepare device for normal usage.
 */
void BMP180_initialize(void) // инициализаци€ 
{
    if (devAddr==0) devAddr = BMP180_DEFAULT_ADDRESS;
    // load sensor's calibration constants
    BMP180_loadCalibration(); // чтение калибровочных €чеек (регистров)
	//BMP180_setControl(BMP180_MODE_TEMPERATURE|BMP180_MODE_PRESSURE_0);
}

/**
 * Verify the device is connected and available.
 */
bool BMP180_testConnection(void)
{
    // test for a response, though this is very basic
    return I2C_readByte(devAddr, BMP180_RA_AC1_H, buffer, 1000) == 1;
}

/* calibration register methods */

void BMP180_loadCalibration(void)
{
    uint8_t buf2[22];
    I2C_readBytes(devAddr, BMP180_RA_AC1_H, 22, buf2, 1000); // чтение 22 €чеек начина€ с јј 
    ac1 = ((int16_t)buf2[0] << 8) + buf2[1];// объединение 2х регистров в 1 коэф.
    ac2 = ((int16_t)buf2[2] << 8) + buf2[3];
    ac3 = ((int16_t)buf2[4] << 8) + buf2[5];
    ac4 = ((uint16_t)buf2[6] << 8) + buf2[7];
    ac5 = ((uint16_t)buf2[8] << 8) + buf2[9];
    ac6 = ((uint16_t)buf2[10] << 8) + buf2[11];
    b1 = ((int16_t)buf2[12] << 8) + buf2[13];
    b2 = ((int16_t)buf2[14] << 8) + buf2[15];
    mb = ((int16_t)buf2[16] << 8) + buf2[17];
    mc = ((int16_t)buf2[18] << 8) + buf2[19];
    md = ((int16_t)buf2[20] << 8) + buf2[21];
    calibrationLoaded = 1;
}

#ifdef BMP180_INCLUDE_INDIVIDUAL_CALIBRATION_ACCESS // если присутствует указатель 
int16_t BMP180_getAC1(void)
{
    if (calibrationLoaded) return ac1;
    I2C_readBytes(devAddr, BMP180_RA_AC1_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getAC2(void)
{
    if (calibrationLoaded) return ac2;
    I2C_readBytes(devAddr, BMP180_RA_AC2_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getAC3(void)
{
    if (calibrationLoaded) return ac3;
    I2C_readBytes(devAddr, BMP180_RA_AC3_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

uint16_t BMP180_getAC4(void)
{
    if (calibrationLoaded) return ac4;
    I2C_readBytes(devAddr, BMP180_RA_AC4_H, 2, buffer);
    return ((uint16_t)buffer[1] << 8) + buffer[0];
}

uint16_t BMP180_getAC5(void)
{
    if (calibrationLoaded) return ac5;
    I2C_readBytes(devAddr, BMP180_RA_AC5_H, 2, buffer);
    return ((uint16_t)buffer[1] << 8) + buffer[0];
}

uint16_t BMP180_getAC6(void)
{
    if (calibrationLoaded) return ac6;
    I2C_readBytes(devAddr, BMP180_RA_AC6_H, 2, buffer);
    return ((uint16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getB1(void)
{
    if (calibrationLoaded) return b1;
    I2C_readBytes(devAddr, BMP180_RA_B1_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getB2(void)
{
    if (calibrationLoaded) return b2;
    I2C_readBytes(devAddr, BMP180_RA_B2_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getMB(void)
{
    if (calibrationLoaded) return mb;
    I2C_readBytes(devAddr, BMP180_RA_MB_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getMC(void)
{
    if (calibrationLoaded) return mc;
    I2C_readBytes(devAddr, BMP180_RA_MC_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}

int16_t BMP180_getMD(void)
{
    if (calibrationLoaded) return md;
    I2C_readBytes(devAddr, BMP180_RA_MD_H, 2, buffer);
    return ((int16_t)buffer[1] << 8) + buffer[0];
}
#endif

/* control register methods */

uint8_t BMP180_getControl(void) // считать байт управлени€
{
    I2C_readByte(devAddr, BMP180_RA_CONTROL, buffer, 1000);
    return buffer[0];
}
void BMP180_setControl(uint8_t value) // установка байт управлени€
{
    I2C_writeByte(devAddr, BMP180_RA_CONTROL, value);
    measureMode = value;
}

/* measurement register methods */

uint16_t BMP180_getMeasurement2(void) // 
{
    I2C_readBytes(devAddr, BMP180_RA_MSB, 2, buffer, 1000);
    return ((uint16_t) buffer[0] << 8) + buffer[1];
}
uint32_t BMP180_getMeasurement3(void)
{
    I2C_readBytes(devAddr, BMP180_RA_MSB, 3, buffer, 1000);
    return ((uint32_t)buffer[0] << 16) + ((uint16_t)buffer[1] << 8) + buffer[2];
}
uint8_t BMP180_getMeasureDelayMilliseconds(uint8_t mode)
{
    if (mode == 0) mode = measureMode;
    if (measureMode == 0x2E) return 5;
    else if (measureMode == 0x34) return 5;
    else if (measureMode == 0x74) return 8;
    else if (measureMode == 0xB4) return 14;
    else if (measureMode == 0xF4) return 26;
    return 0; // invalid mode
}
uint16_t BMP180_getMeasureDelayMicroseconds(uint8_t mode)
{
    if (mode == 0) mode = measureMode;
    if (measureMode == 0x2E) return 4500;
    else if (measureMode == 0x34) return 4500;
    else if (measureMode == 0x74) return 7500;
    else if (measureMode == 0xB4) return 13500;
    else if (measureMode == 0xF4) return 25500;
    return 0; // invalid mode
}

uint16_t BMP180_getRawTemperature(void)
{
    if (measureMode == 0x2E) return BMP180_getMeasurement2();
    return 0; // wrong measurement mode for temperature request
}

float BMP180_getTemperatureC(void)
{
    BMP180_setControl(BMP180_MODE_TEMPERATURE);
        _delay_ms(BMP180_getMeasureDelayMilliseconds(BMP180_MODE_TEMPERATURE));
	/*
    Datasheet formula:
        UT = raw temperature
        X1 = (UT - AC6) * AC5 / 2^15
        X2 = MC * 2^11 / (X1 + MD)
        B5 = X1 + X2
        T = (B5 + 8) / 2^4
    */
    int32_t ut = BMP180_getRawTemperature();
    int32_t x1 = ((ut - (int32_t)ac6) * (int32_t)ac5) >> 15;
    int32_t x2 = ((int32_t)mc << 11) / (x1 + md);
    b5 = x1 + x2;
    return (float)((b5 + 8) >> 4) / 10.0f;
}

float BMP180_getTemperatureF(void)
{
    return BMP180_getTemperatureC() * 9.0f / 5.0f + 32;
}

uint32_t BMP180_getRawPressure(void)
{
    if (measureMode & 0x34) return BMP180_getMeasurement3() >> (8 - ((measureMode & 0xC0) >> 6));
    return 0; // wrong measurement mode for pressure request
}

float BMP180_getPressure(uint8_t bmp180_mode)
{
	BMP180_setControl(bmp180_mode);
        _delay_ms(BMP180_getMeasureDelayMilliseconds(bmp180_mode));
    /*
    Datasheet forumla
        UP = raw pressure
        B6 = B5 - 4000
        X1 = (B2 * (B6 * B6 / 2^12)) / 2^11
        X2 = AC2 * B6 / 2^11
        X3 = X1 + X2
        B3 = ((AC1 * 4 + X3) << oss + 2) / 4
        X1 = AC3 * B6 / 2^13
        X2 = (B1 * (B6 * B6 / 2^12)) / 2^16
        X3 = ((X1 + X2) + 2) / 2^2
        B4 = AC4 * (unsigned long)(X3 + 32768) / 2^15
        B7 = ((unsigned long)UP - B3) * (50000 >> oss)
        if (B7 < 0x80000000) { p = (B7 * 2) / B4 }
        else { p = (B7 / B4) * 2 }
        X1 = (p / 2^8) * (p / 2^8)
        X1 = (X1 * 3038) / 2^16
        X2 = (-7357 * p) / 2^16
        p = p + (X1 + X2 + 3791) / 2^4
    */
    uint32_t up = BMP180_getRawPressure();
    uint8_t oss = (measureMode & 0xC0) >> 6;
    int32_t p;
    int32_t b6 = b5 - 4000;
    int32_t x1 = ((int32_t)b2 * ((b6 * b6) >> 12)) >> 11;
    int32_t x2 = ((int32_t)ac2 * b6) >> 11;
    int32_t x3 = x1 + x2;
    int32_t b3 = ((((int32_t)ac1 * 4 + x3) << oss) + 2) >> 2;
    x1 = ((int32_t)ac3 * b6) >> 13;
    x2 = ((int32_t)b1 * ((b6 * b6) >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    uint32_t b4 = ((uint32_t)ac4 * (uint32_t)(x3 + 32768)) >> 15;
    uint32_t b7 = ((uint32_t)up - b3) * (uint32_t)(50000UL >> oss);
    if (b7 < 0x80000000)
    {
        p = (b7 << 1) / b4;
    }
    else
    {
        p = (b7 / b4) << 1;
    }
    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    return p + ((x1 + x2 + (int32_t)3791) >> 4);
}

float BMP180_getAltitude(float pressure, float seaLevelPressure)
{
    if (seaLevelPressure == 0) seaLevelPressure = 101325;
    return 44330 * (1.0 - pow(pressure / seaLevelPressure, 0.1903));
}
