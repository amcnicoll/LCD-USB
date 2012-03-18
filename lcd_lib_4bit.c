//*****************************************************************************
//
// File Name	: 'lcd_lib.c'
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
#include "lcd_lib_4bit.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


// Channel A begins here!!!
static void CHA_LCDMix_4Bit(uint8_t data);
const uint8_t LcdCustomChar[] PROGMEM=//define 8 custom LCD chars
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // not used - empty character
	0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, // 1. 1/5 full progress block
	0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, // 2. 2/5 full progress block
	0x00, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x00, // 3. 3/5 full progress block
	0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x00, // 4. 4/5 full progress block
	0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // 5. 5/5 full progress block
	0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, // 6. left bookend
	0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x18  // 7. right bookend
};

//sets four port pins to corresponding nibble
//for high nibble use mask data & 0b11110000
//for low nibble use (data & 0b00001111)<<4
static void CHA_LCDMix_4Bit(uint8_t data)
{
  if((data)&(0b10000000)) CHA_LDPD7 |=1<<CHA_LCD_D7;
    else CHA_LDPD7 &=~(1<<CHA_LCD_D7);
  if((data)&(0b01000000)) CHA_LDPD6 |=1<<CHA_LCD_D6;
    else CHA_LDPD6 &=~(1<<CHA_LCD_D6);
  if((data)&(0b00100000)) CHA_LDPD5 |=1<<CHA_LCD_D5;
    else CHA_LDPD5&=~(1<<CHA_LCD_D5);
  if((data)&(0b00010000)) CHA_LDPD4 |=1<<CHA_LCD_D4;
    else CHA_LDPD4 &=~(1<<CHA_LCD_D4);	
}

void CHA_LCDinit(void)//Initializes LCD
{
	//4 mixed bit part
	_delay_ms(15);
	//set data direction
	CHA_LDDD4 |=1<<CHA_LCD_D4;
	CHA_LDDD5 |=1<<CHA_LCD_D5;
	CHA_LDDD6 |=1<<CHA_LCD_D6;
	CHA_LDDD7 |=1<<CHA_LCD_D7;
	//control direction pins
	CHA_LDDRS |=1<<CHA_LCD_RS;
	CHA_LDDRW |=1<<CHA_LCD_RW;
	CHA_LDDE |=1<<CHA_LCD_E;
	//zero to data pins
	CHA_LCDMix_4Bit(0b00000000);
	//zero to control pins
	CHA_LDPRS &=~(1<<CHA_LCD_RS);
	CHA_LDPRW &=~(1<<CHA_LCD_RW);
	CHA_LDPE &=~(1<<CHA_LCD_E);
   //---------one------
	CHA_LCDMix_4Bit(0b00110000);
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	_delay_ms(1);
	//-----------two-----------
	CHA_LCDMix_4Bit(0b00110000);
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	_delay_ms(1);
	//-------three-------------
	CHA_LCDMix_4Bit(0b00100000);
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	_delay_ms(1);
	//--------4 bit--dual line---------------
	CHA_LCDsendCommand(0b00101000);
   //-----increment address, invisible cursor shift------
	CHA_LCDsendCommand(0b00001100);

		//init 8 custom chars
	uint8_t ch=0, chn=0;
	while(ch<64)
	{
		CHA_LCDdefinechar((LcdCustomChar+ch),chn++);
		ch=ch+8;
	}
}	
void CHA_LCDsendChar(uint8_t ch)		//Sends Char to LCD
{
	CHA_LCDMix_4Bit(ch & 0b11110000);
	CHA_LDPRS |=1<<CHA_LCD_RS;
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	CHA_LDPRS &=~(1<<CHA_LCD_RS);
	_delay_ms(1);
	CHA_LCDMix_4Bit((ch & 0b00001111)<<4);
	CHA_LDPRS |=1<<CHA_LCD_RS;
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	CHA_LDPRS &=~(1<<CHA_LCD_RS);
	_delay_ms(1);
}
void CHA_LCDsendCommand(uint8_t cmd)	//Sends Command to LCD
{
	CHA_LCDMix_4Bit(cmd & 0b11110000);
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	_delay_ms(1);
	CHA_LCDMix_4Bit((cmd & 0b00001111)<<4);
	CHA_LDPE |=1<<CHA_LCD_E;		
	_delay_ms(1);
	CHA_LDPE &=~(1<<CHA_LCD_E);
	_delay_ms(1);
}		
void CHA_LCDclr(void)				//Clears LCD
{
	CHA_LCDsendCommand(1<<LCD_CLR);
}
void CHA_LCDstringLine(uint8_t* data, uint8_t ln)	//Outputs string to line ln, where 0 corresponds to top line.
{
	// Send to correct line beginning
	if (ln)
		CHA_LCDsendCommand(0xC0);
	else
		CHA_LCDsendCommand(0x80);

	// Print data. Empty (0) chars are printed as spaces as defined in custom chars.
	for(uint8_t i=0; i<16; i++){
		CHA_LCDsendChar(data[i]);
	}
}
void CHA_LCDGotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	}
	// set data address
	CHA_LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);
	
}
void CHA_LCDdefinechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a=(char_code<<3)|0x40;
	for (i=0; i<8; i++){
		pcc=pgm_read_byte(&pc[i]);
		CHA_LCDsendCommand(a++);
		CHA_LCDsendChar(pcc);
		}
}
void CHA_LCDshiftLeft(uint8_t n)	//Scroll n of characters Right
{
	for (uint8_t i=0;i<n;i++)
	{
		CHA_LCDsendCommand(0x18);
	}
}
void CHA_LCDshiftRight(uint8_t n)	//Scroll n of characters Left
{
	for (uint8_t i=0;i<n;i++)
	{
		CHA_LCDsendCommand(0x1E);
	}
}
void CHA_LCDcursorLeft(uint8_t n)	//Moves cursor by n positions left
{
	for (uint8_t i=0;i<n;i++)
	{
		CHA_LCDsendCommand(0x10);
	}
}
void CHA_LCDcursorRight(uint8_t n)	//Moves cursor by n positions left
{
	for (uint8_t i=0;i<n;i++)
	{
		CHA_LCDsendCommand(0x14);
	}
}

// CHANNEL B BEGINS HERE!

static void CHB_LCDMix_4Bit(uint8_t data);

//sets four port pins to corresponding nibble
//for high nibble use mask data & 0b11110000
//for low nibble use (data & 0b00001111)<<4
static void CHB_LCDMix_4Bit(uint8_t data)
{
  if((data)&(0b10000000)) CHB_LDPD7 |=1<<CHB_LCD_D7;
    else CHB_LDPD7 &=~(1<<CHB_LCD_D7);
  if((data)&(0b01000000)) CHB_LDPD6 |=1<<CHB_LCD_D6;
    else CHB_LDPD6 &=~(1<<CHB_LCD_D6);
  if((data)&(0b00100000)) CHB_LDPD5 |=1<<CHB_LCD_D5;
    else CHB_LDPD5&=~(1<<CHB_LCD_D5);
  if((data)&(0b00010000)) CHB_LDPD4 |=1<<CHB_LCD_D4;
    else CHB_LDPD4 &=~(1<<CHB_LCD_D4);
}

void CHB_LCDinit(void)//Initializes LCD
{
	//4 mixed bit part
	_delay_ms(15);
	//set data direction
	CHB_LDDD4 |=1<<CHB_LCD_D4;
	CHB_LDDD5 |=1<<CHB_LCD_D5;
	CHB_LDDD6 |=1<<CHB_LCD_D6;
	CHB_LDDD7 |=1<<CHB_LCD_D7;
	//control direction pins
	CHB_LDDRS |=1<<CHB_LCD_RS;
	CHB_LDDRW |=1<<CHB_LCD_RW;
	CHB_LDDE |=1<<CHB_LCD_E;
	//zero to data pins
	CHB_LCDMix_4Bit(0b00000000);
	//zero to control pins
	CHB_LDPRS &=~(1<<CHB_LCD_RS);
	CHB_LDPRW &=~(1<<CHB_LCD_RW);
	CHB_LDPE &=~(1<<CHB_LCD_E);
   //---------one------
	CHB_LCDMix_4Bit(0b00110000);
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	_delay_ms(1);
	//-----------two-----------
	CHB_LCDMix_4Bit(0b00110000);
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	_delay_ms(1);
	//-------three-------------
	CHB_LCDMix_4Bit(0b00100000);
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	_delay_ms(1);
	//--------4 bit--dual line---------------
	CHB_LCDsendCommand(0b00101000);
   //-----increment address, invisible cursor shift------
	CHB_LCDsendCommand(0b00001100);

		//init 8 custom chars
	uint8_t ch=0, chn=0;
	while(ch<64)
	{
		CHB_LCDdefinechar((LcdCustomChar+ch),chn++);
		ch=ch+8;
	}
}
void CHB_LCDsendChar(uint8_t ch)		//Sends Char to LCD
{
	CHB_LCDMix_4Bit(ch & 0b11110000);
	CHB_LDPRS |=1<<CHB_LCD_RS;
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	CHB_LDPRS &=~(1<<CHB_LCD_RS);
	_delay_ms(1);
	CHB_LCDMix_4Bit((ch & 0b00001111)<<4);
	CHB_LDPRS |=1<<CHB_LCD_RS;
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	CHB_LDPRS &=~(1<<CHB_LCD_RS);
	_delay_ms(1);
}
void CHB_LCDsendCommand(uint8_t cmd)	//Sends Command to LCD
{
	CHB_LCDMix_4Bit(cmd & 0b11110000);
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	_delay_ms(1);
	CHB_LCDMix_4Bit((cmd & 0b00001111)<<4);
	CHB_LDPE |=1<<CHB_LCD_E;
	_delay_ms(1);
	CHB_LDPE &=~(1<<CHB_LCD_E);
	_delay_ms(1);
}
void CHB_LCDclr(void)				//Clears LCD
{
	CHB_LCDsendCommand(1<<LCD_CLR);
}
void CHB_LCDstringLine(uint8_t* data, uint8_t ln)	//Outputs string to line ln, where 0 corresponds to top line.
{
	// Send to correct line beginning
	if (ln)
		CHB_LCDsendCommand(0xC0);
	else
		CHB_LCDsendCommand(0x80);

	// Print data. Empty (0) chars are printed as spaces as defined in custom chars.
	for(uint8_t i=0; i<16; i++){
		CHB_LCDsendChar(data[i]);
	}
}
void CHB_LCDGotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
	}
	// set data address
	CHB_LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);

}
void CHB_LCDdefinechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a=(char_code<<3)|0x40;
	for (i=0; i<8; i++){
		pcc=pgm_read_byte(&pc[i]);
		CHB_LCDsendCommand(a++);
		CHB_LCDsendChar(pcc);
		}
}
void CHB_LCDshiftLeft(uint8_t n)	//Scroll n of characters Right
{
	for (uint8_t i=0;i<n;i++)
	{
		CHB_LCDsendCommand(0x18);
	}
}
void CHB_LCDshiftRight(uint8_t n)	//Scroll n of characters Left
{
	for (uint8_t i=0;i<n;i++)
	{
		CHB_LCDsendCommand(0x1E);
	}
}
void CHB_LCDcursorLeft(uint8_t n)	//Moves cursor by n positions left
{
	for (uint8_t i=0;i<n;i++)
	{
		CHB_LCDsendCommand(0x10);
	}
}
void CHB_LCDcursorRight(uint8_t n)	//Moves cursor by n positions left
{
	for (uint8_t i=0;i<n;i++)
	{
		CHB_LCDsendCommand(0x14);
	}
}
