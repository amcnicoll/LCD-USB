//*****************************************************************************
//
// File Name	: 'lcd_lib.h'
// Title		: 8 and 4 bit LCd interface
// Author		: Scienceprog.com - Copyright (C) 2007
// Created		: 2007-03-29
// Revised		: 2007-08-08
// Version		: 1.0
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef LCD_LIB
#define LCD_LIB

#include <inttypes.h>
//******************************************************

#define CHA_LCD_RS	0 	//define MCU pin connected to LCD RS
#define CHA_LCD_RW	1 	//define MCU pin connected to LCD R/W
#define CHA_LCD_E	6	//define MCU pin connected to LCD E
#define CHA_LCD_D4	5	//define MCU pin connected to LCD D4
#define CHA_LCD_D5	4	//define MCU pin connected to LCD D5
#define CHA_LCD_D6	3	//define MCU pin connected to LCD D6
#define CHA_LCD_D7	2	//define MCU pin connected to LCD D7

#define CHB_LCD_RS	0 	//define MCU pin connected to LCD RS
#define CHB_LCD_RW	1 	//define MCU pin connected to LCD R/W
#define CHB_LCD_E	2	//define MCU pin connected to LCD E
#define CHB_LCD_D4	3	//define MCU pin connected to LCD D4
#define CHB_LCD_D5	4	//define MCU pin connected to LCD D5
#define CHB_LCD_D6	7	//define MCU pin connected to LCD D6
#define CHB_LCD_D7	6	//define MCU pin connected to LCD D7

#define CHA_LDPRS PORTD		//RS pin assignment
#define CHA_LDDRS DDRD
#define CHA_LDPRW PORTD		//RW pin assignment
#define CHA_LDDRW DDRD
#define CHA_LDPE PORTD		//E pin assignment
#define CHA_LDDE DDRD
#define CHA_LDPD4 PORTD		//D4 pin assignment
#define CHA_LDDD4 DDRD
#define CHA_LDPD5 PORTD		//D5 pin assignment
#define CHA_LDDD5 DDRD
#define CHA_LDPD6 PORTD		//D6 pin assignment
#define CHA_LDDD6 DDRD
#define CHA_LDPD7 PORTD		//D7 pin assignment
#define CHA_LDDD7 DDRD

#define CHB_LDPRS PORTB		//RS pin assignment
#define CHB_LDDRS DDRB
#define CHB_LDPRW PORTB		//RW pin assignment
#define CHB_LDDRW DDRB
#define CHB_LDPE PORTB		//E pin assignment
#define CHB_LDDE DDRB
#define CHB_LDPD4 PORTB		//D4 pin assignment
#define CHB_LDDD4 DDRB
#define CHB_LDPD5 PORTB		//D5 pin assignment
#define CHB_LDDD5 DDRB
#define CHB_LDPD6 PORTB		//D6 pin assignment
#define CHB_LDDD6 DDRB
#define CHB_LDPD7 PORTB		//D7 pin assignment
#define CHB_LDDD7 DDRB

// Some commands for LCD driver
#define LCD_CLR             0	//DB0: clear display
#define LCD_CGRAM           6	//DB6: set CG RAM address
#define LCD_DDRAM           7	//DB7: set DD RAM address

// Cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54


void CHA_LCDsendChar(uint8_t);		//forms data ready to send to LCD
void CHA_LCDsendCommand(uint8_t);	//forms data ready to send to LCD
void CHA_LCDinit(void);			//Initializes LCD
void CHA_LCDclr(void);				//Clears LCD
void CHA_LCDstringLine(uint8_t*, uint8_t);	//Outputs string to LCD
void CHA_LCDGotoXY(uint8_t, uint8_t);	//Cursor to X Y position
void CHA_LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM 
void CHA_LCDshiftRight(uint8_t);	//shift by n characters Right
void CHA_LCDshiftLeft(uint8_t);	//shift by n characters Left
void CHA_LCDcursorLeft(uint8_t);	//Shift cursor left by n
void CHA_LCDcursorRight(uint8_t);	//shift cursor right by n

void CHB_LCDsendChar(uint8_t);		//forms data ready to send to LCD
void CHB_LCDsendCommand(uint8_t);	//forms data ready to send to LCD
void CHB_LCDinit(void);			//Initializes LCD
void CHB_LCDclr(void);				//Clears LCD
void CHB_LCDstringLine(uint8_t*, uint8_t);	//Outputs string to LCD
void CHB_LCDGotoXY(uint8_t, uint8_t);	//Cursor to X Y position
void CHB_LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM
void CHB_LCDshiftRight(uint8_t);	//shift by n characters Right
void CHB_LCDshiftLeft(uint8_t);	//shift by n characters Left
void CHB_LCDcursorLeft(uint8_t);	//Shift cursor left by n
void CHB_LCDcursorRight(uint8_t);	//shift cursor right by n

#endif

