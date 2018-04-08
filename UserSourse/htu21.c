#include "htu21.h"

///////////////////////////////////////////////////////////////////////////////////////////////
boolean htu21_begin(void) {
//  uint8_t tempr=0;
  reset();

  I2C_StartTransmission(I2C1,I2C_Direction_Transmitter,HTU21DF_I2CADDR<<1);
  I2C_WriteData(I2C1, HTU21DF_READREG);
  I2C_StopTransmission(I2C1);
  I2C_StartTransmission(I2C1,I2C_Direction_Receiver,HTU21DF_I2CADDR<<1);
	if(I2C_ReadData(I2C1) == 0x02){
		I2C_StopTransmission(I2C1);
		return (0x01);}
	else{
		I2C_StopTransmission(I2C1);
  return (0);} 
}
///////////////////////////////////////////////////////////////////////////////////////////////
void reset(void) {
 I2C_StartTransmission(I2C1,I2C_Direction_Transmitter,HTU21DF_I2CADDR<<1);
  I2C_WriteData(I2C1, HTU21DF_RESET);
  I2C_StopTransmission(I2C1);
  _delay_ms(15);
}

///////////////////////////////////////////////////////////////////////////////////////////////
float readTemperature(void) {
  

	I2C_StartTransmission(I2C1,I2C_Direction_Transmitter,HTU21DF_I2CADDR<<1);
  I2C_WriteData(I2C1, HTU21DF_READTEMP);
  I2C_StopTransmission(I2C1);
  
  _delay_ms(50); 
  I2C_StartTransmission(I2C1,I2C_Direction_Receiver,HTU21DF_I2CADDR<<1);


  uint16_t t = I2C_ReadData(I2C1);
  t <<= 8;
  t |= I2C_ReadData(I2C1);

  uint8_t crc = I2C_ReadData(I2C1);

  float tempr = t;
  tempr *= 175.72;
  tempr /= 65536;
  tempr -= 46.85;

  return tempr;
}
  
///////////////////////////////////////////////////////////////////////////////////////////////
float readHumidity(void) {
  // i2c start
	I2C_StartTransmission(I2C1,I2C_Direction_Transmitter,HTU21DF_I2CADDR<<1);
  I2C_WriteData(I2C1, HTU21DF_READHUM);
  I2C_StopTransmission(I2C1);
  
  
  _delay_ms(50); // ждём пока измереет 
  
  I2C_StartTransmission(I2C1,I2C_Direction_Receiver,HTU21DF_I2CADDR<<1);
 

  uint16_t h = I2C_ReadData(I2C1);
  h <<= 8;
  h |= I2C_ReadData(I2C1);

  uint8_t crc =I2C_ReadData(I2C1);

  float hum = h;
  hum *= 125;
  hum /= 65536;
  hum -= 6;

  return hum;
}


