#include <avr/io.h>
#include <inttypes.h>
#include "lcd_lib_4bit.h"
#include <util/delay.h>
#include <stdlib.h>

// Macros
#define set_low(port,pin) port &= ~(1<<pin)
#define set_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

int main(void)
{
	CHA_LCDinit();//init LCD bit, dual line, cursor right
	CHA_LCDclr();//clears LCD
	//CHB_LCDinit();//init LCD bit, dual line, cursor right
	//CHB_LCDclr();//clears LCD
	uint8_t lna0[16] = {72,68,68,6,5,5,5,5,3,0,0,0,7,53,55,37};
	while(1)//loop demos
	{
		// Build a random string
		//for (uint8_t h=0;h<5;h++){
		//	lna0[h]= (rand() % 20)+65;
		//}
		_delay_ms(3000);
		CHA_LCDclr();
		CHA_LCDstringLine(lna0,rand() % 2);
		//uint8_t derp[16] = {72,101,108,108,111,44,32,87,111,114,108,100,33};
		//CHB_LCDstringLine(derp, 0);
	}
	return 0;
}
