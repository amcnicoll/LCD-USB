#include <avr/io.h>
#include <inttypes.h>
#include "lcd_lib_4bit.h"
#include <util/delay.h>
#include <stdlib.h>

//lulz
// Macros
#define set_low(port,pin) port &= ~(1<<pin)
#define set_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

int main(void)
{
	_delay_ms(500); 		// Wait for power fluctuations to clear
	CHA_LCDinit();			// init LCD bit, dual line, cursor right
	CHA_LCDclr();			// clears LCD
	CHB_LCDinit();			// init LCD bit, dual line, cursor right
	CHB_LCDclr();			// clears LCD
	uint8_t lna0[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		// Screen A, Line 0
	uint8_t lna1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		// Screen A, Line 1
	uint8_t lnb0[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		// Screen B, Line 0
	uint8_t lnb1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		// Screen B, Line 1
	//uint8_t lna0[16] = {72,68,68,6,5,5,5,5,3,0,0,0,7,53,55,37};		// Test string: 57% HDD
	while(1)
	{
		// Build a random string
		for (uint8_t h=0;h<5;h++){
			lna0[h]= (rand() % 20)+65;
		}
		_delay_ms(3000);
		CHA_LCDclr();
		CHA_LCDstringLine(lna0,rand() % 2);
		CHB_LCDclr();
		CHB_LCDstringLine(lna0,rand() % 2);
	}
	return 0;
}
