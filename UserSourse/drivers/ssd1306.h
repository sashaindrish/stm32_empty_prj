#ifndef __SSD1306_H
#define __SSD1306_H

#include "stm32f10x.h"
#include "i2c.h"

#include "fonts.h"
#include "stdlib.h"
#include "string.h"

//extern uint8_t LCD_Buffer[][22];
//extern uint8_t LCD_X,LCD_Y;
extern I2C_InitTypeDef i2c;

#define SSD1306_I2C_ADDRESS									0x78
#define SSD1306_I2C_SPEED               	100000//300000
#define DC_BIT                     6
#define CONTROL_BYTE_COMMAND       0 << DC_BIT  
#define CONTROL_BYTE_DATA          1 << DC_BIT 

// gpio LCD

// size 
#define SSD1306_LCDWIDTH                  	128
#define SSD1306_LCDHEIGHT                 	64
#define SSD1306_DEFAULT_SPACE				5
// Commands
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define COMAND		0x00
#define DATA		0x40

/*
uint8_t LCD_BUF[][22] = { 
	{0x00, 0x00, 0x00, 0x00, 0x00},// (space)
	{0x00, 0x00, 0x5F, 0x00, 0x00},// !
	{0x00, 0x07, 0x00, 0x07, 0x00},// "
	{0x14, 0x7F, 0x14, 0x7F, 0x14},// #
	{0x24, 0x2A, 0x7F, 0x2A, 0x12},// $
	{0x23, 0x13, 0x08, 0x64, 0x62},// %
	{0x36, 0x49, 0x55, 0x22, 0x50},// &
	{0x00, 0x05, 0x03, 0x00, 0x00},// '
	{0x00, 0x1C, 0x22, 0x41, 0x00},// (
	{0x00, 0x41, 0x22, 0x1C, 0x00},// )
	{0x08, 0x2A, 0x1C, 0x2A, 0x08},// *
	{0x08, 0x08, 0x3E, 0x08, 0x08},// +
	{0x00, 0x50, 0x30, 0x00, 0x00},// ,
	{0x08, 0x08, 0x08, 0x08, 0x08},// -
	{0x00, 0x30, 0x30, 0x00, 0x00},// .
	{0x20, 0x10, 0x08, 0x04, 0x02},// /
	{0x3E, 0x51, 0x49, 0x45, 0x3E},// 0
	{0x00, 0x42, 0x7F, 0x40, 0x00},// 1
	{0x42, 0x61, 0x51, 0x49, 0x46},// 2
	{0x21, 0x41, 0x45, 0x4B, 0x31},// 3
	{0x18, 0x14, 0x12, 0x7F, 0x10},// 4
	{0x27, 0x45, 0x45, 0x45, 0x39},// 5
	{0x3C, 0x4A, 0x49, 0x49, 0x30},// 6
	{0x01, 0x71, 0x09, 0x05, 0x03},// 7
	{0x36, 0x49, 0x49, 0x49, 0x36},// 8
	{0x06, 0x49, 0x49, 0x29, 0x1E},// 9
	{0x00, 0x36, 0x36, 0x00, 0x00},// :
	{0x00, 0x56, 0x36, 0x00, 0x00},// ;
	{0x00, 0x08, 0x14, 0x22, 0x41},// <
	{0x14, 0x14, 0x14, 0x14, 0x14},// =
	{0x41, 0x22, 0x14, 0x08, 0x00},// >
	{0x02, 0x01, 0x51, 0x09, 0x06},// ?
	{0x32, 0x49, 0x79, 0x41, 0x3E},// @
	{0x7E, 0x11, 0x11, 0x11, 0x7E},// A
	{0x7F, 0x49, 0x49, 0x49, 0x36},// B
	{0x3E, 0x41, 0x41, 0x41, 0x22},// C
	{0x7F, 0x41, 0x41, 0x22, 0x1C},// D
	{0x7F, 0x49, 0x49, 0x49, 0x41},// E
	{0x7F, 0x09, 0x09, 0x01, 0x01},// F
	{0x3E, 0x41, 0x41, 0x51, 0x32},// G
	{0x7F, 0x08, 0x08, 0x08, 0x7F},// H
	{0x00, 0x41, 0x7F, 0x41, 0x00},// I
	{0x20, 0x40, 0x41, 0x3F, 0x01},// J
	{0x7F, 0x08, 0x14, 0x22, 0x41},// K
	{0x7F, 0x40, 0x40, 0x40, 0x40},// L
	{0x7F, 0x02, 0x04, 0x02, 0x7F},// M
	{0x7F, 0x04, 0x08, 0x10, 0x7F},// N
	{0x3E, 0x41, 0x41, 0x41, 0x3E},// O
	{0x7F, 0x09, 0x09, 0x09, 0x06},// P
	{0x3E, 0x41, 0x51, 0x21, 0x5E},// Q
	{0x7F, 0x09, 0x19, 0x29, 0x46},// R
	{0x46, 0x49, 0x49, 0x49, 0x31},// S
	{0x01, 0x01, 0x7F, 0x01, 0x01},// T
	{0x3F, 0x40, 0x40, 0x40, 0x3F},// U
	{0x1F, 0x20, 0x40, 0x20, 0x1F},// V
	{0x7F, 0x20, 0x18, 0x20, 0x7F},// W
	{0x63, 0x14, 0x08, 0x14, 0x63},// X
	{0x03, 0x04, 0x78, 0x04, 0x03},// Y
	{0x61, 0x51, 0x49, 0x45, 0x43},// Z
	{0x00, 0x00, 0x7F, 0x41, 0x41},// [
	{0x02, 0x04, 0x08, 0x10, 0x20},// "\"
	{0x41, 0x41, 0x7F, 0x00, 0x00},// ]
	{0x04, 0x02, 0x01, 0x02, 0x04},// ^
	{0x40, 0x40, 0x40, 0x40, 0x40},// _
	{0x00, 0x01, 0x02, 0x04, 0x00},// `
	{0x20, 0x54, 0x54, 0x54, 0x78},// a
	{0x7F, 0x48, 0x44, 0x44, 0x38},// b
	{0x38, 0x44, 0x44, 0x44, 0x20},// c
	{0x38, 0x44, 0x44, 0x48, 0x7F},// d
	{0x38, 0x54, 0x54, 0x54, 0x18},// e
	{0x08, 0x7E, 0x09, 0x01, 0x02},// f
	{0x08, 0x14, 0x54, 0x54, 0x3C},// g
	{0x7F, 0x08, 0x04, 0x04, 0x78},// h
	{0x00, 0x44, 0x7D, 0x40, 0x00},// i
	{0x20, 0x40, 0x44, 0x3D, 0x00},// j
	{0x00, 0x7F, 0x10, 0x28, 0x44},// k
	{0x00, 0x41, 0x7F, 0x40, 0x00},// l
	{0x7C, 0x04, 0x18, 0x04, 0x78},// m
	{0x7C, 0x08, 0x04, 0x04, 0x78},// n
	{0x38, 0x44, 0x44, 0x44, 0x38},// o
	{0x7C, 0x14, 0x14, 0x14, 0x08},// p
	{0x08, 0x14, 0x14, 0x18, 0x7C},// q
	{0x7C, 0x08, 0x04, 0x04, 0x08},// r
	{0x48, 0x54, 0x54, 0x54, 0x20},// s
	{0x04, 0x3F, 0x44, 0x40, 0x20},// t
	{0x3C, 0x40, 0x40, 0x20, 0x7C},// u
	{0x1C, 0x20, 0x40, 0x20, 0x1C},// v
	{0x3C, 0x40, 0x30, 0x40, 0x3C},// w
	{0x44, 0x28, 0x10, 0x28, 0x44},// x
	{0x0C, 0x50, 0x50, 0x50, 0x3C},// y
	{0x44, 0x64, 0x54, 0x4C, 0x44},// z
	{0x00, 0x08, 0x36, 0x41, 0x00},// {
	{0x00, 0x00, 0x7F, 0x00, 0x00},// |
	{0x00, 0x41, 0x36, 0x08, 0x00},// }
	{0x02, 0x01, 0x02, 0x04, 0x02},// ~
	{0x08, 0x1C, 0x2A, 0x08, 0x08} // <-
};

*/
/**
 * This SSD1306 LCD uses I2C for communication
 *
 * Library features functions for drawing lines, rectangles and circles.
 *
 * It also allows you to draw texts and characters using appropriate functions provided in library.
 *
 * Default pinout
 *
SSD1306    |STM32F10x    |DESCRIPTION
VCC        |3.3V         |
GND        |GND          |
SCL        |PB6          |Serial clock line
SDA        |PB7          |Serial data line
 */





/* I2C address */
#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR         0x78
//#define SSD1306_I2C_ADDR       0x7A
#endif

/* SSD1306 settings */
/* SSD1306 width in pixels */
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH            128
#endif
/* SSD1306 LCD height in pixels */
#ifndef SSD1306_HEIGHT
#define SSD1306_HEIGHT           64
#endif

/*!< Black color, no pixel */
#define SSD1306_COLOR_BLACK 0x00
/*!< Pixel is set. Color depends on LCD */
#define SSD1306_COLOR_WHITE 0x01



/**
 * @brief  Initializes SSD1306 LCD
 * @param  None
 * @retval Initialization status:
 *           - 0: LCD was not detected on I2C port
 *           - > 0: LCD initialized OK and ready to use
 */
uint8_t SSD1306_Init(void);

/** 
 * @brief  Updates buffer from internal RAM to LCD
 * @note   This function must be called each time you do some changes to LCD, to update buffer from RAM to LCD
 * @param  None
 * @retval None
 */
void SSD1306_UpdateScreen(void);

/**
 * @brief  Toggles pixels invertion inside internal RAM
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  None
 * @retval None
 */
void SSD1306_ToggleInvert(void);

/** 
 * @brief  Fills entire LCD with desired color
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  Color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_Fill(uint8_t Color);

/**
 * @brief  Draws pixel at desired location
 * @note   @ref SSD1306_UpdateScreen() must called after that in order to see updated LCD screen
 * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
 * @param  color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawPixel(uint16_t x, uint16_t y, uint8_t color);

/**
 * @brief  Sets cursor pointer to desired location for strings
 * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
 * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
 * @retval None
 */
void SSD1306_GotoXY(uint16_t x, uint16_t y);

/**
 * @brief  Puts character to internal RAM
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  ch: Character to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval Character written
 */
char SSD1306_Putc(char ch, FontDef_t* Font, uint8_t color);

/**
 * @brief  Puts string to internal RAM
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  *str: String to be written
 * @param  *Font: Pointer to @ref FontDef_t structure with used font
 * @param  color: Color used for drawing. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval Zero on success or character value when function failed
 */
char SSD1306_Puts(char* str, FontDef_t* Font, uint8_t color);

/**
 * @brief  Draws line on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x0: Line X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y0: Line Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  x1: Line X end point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y1: Line Y end point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t c);

/**
 * @brief  Draws rectangle on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c);

/**
 * @brief  Draws filled rectangle on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  w: Rectangle width in units of pixels
 * @param  h: Rectangle height in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t c);

/**
 * @brief  Draws triangle on LCD
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x1: First coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y1: First coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  x2: Second coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y2: Second coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  x3: Third coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y3: Third coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t color);

/**
 * @brief  Draws circle to STM buffer
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: X location for center of circle. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Y location for center of circle. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  r: Circle radius in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t c);

/**
 * @brief  Draws filled circle to STM buffer
 * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
 * @param  x: X location for center of circle. Valid input is 0 to SSD1306_WIDTH - 1
 * @param  y: Y location for center of circle. Valid input is 0 to SSD1306_HEIGHT - 1
 * @param  r: Circle radius in units of pixels
 * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
 * @retval None
 */
void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint8_t c);

/**
 * @brief  Writes multi bytes to slave
 * @param  *I2Cx: I2C used
 * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
 * @param  reg: register to write to
 * @param  *data: pointer to data array to write it to slave
 * @param  count: how many bytes will be written
 * @retval None
 */
void ssd1306_image(uint8_t *img, uint8_t frame, uint8_t x, uint8_t y);



/**
 * @brief  Initializes SSD1306 LCD
 * @param  None
 * @retval Initialization status:
 *           - 0: LCD was not detected on I2C port
 *           - > 0: LCD initialized OK and ready to use
 */
//void ssd1306_I2C_Init(void);

/**
 * @brief  Writes single byte to slave
 * @param  *I2Cx: I2C used
 * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
 * @param  reg: register to write to
 * @param  data: data to be written
 * @retval None
 */
//void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);

/**
 * @brief  Writes multi bytes to slave
 * @param  *I2Cx: I2C used
 * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
 * @param  reg: register to write to
 * @param  *data: pointer to data array to write it to slave
 * @param  count: how many bytes will be written
 * @retval None
 */
//void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
//void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);

void SSD1306_WRITECOMMAND(uint8_t command);
void SSD1306_WRITEDATA(uint8_t data);
void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count);


#endif
