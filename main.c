#include <avr/io.h>
#include <inttypes.h>
#include "lcd_lib_4bit.h"
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "usbdrv.h"

// Macros
#define set_low(port,pin) port &= ~(1<<pin)
#define set_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

// Global variables for storing lines
uint8_t lna0[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};				// Screen A, Line 0
uint8_t lna1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};				// Screen A, Line 1
uint8_t lnb0[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};				// Screen B, Line 0
uint8_t lnb1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};				// Screen B, Line 1

// Used for ongoing transmissions
uint8_t buff[16];				// Build transmitted strings here
uint8_t addr;

// Debug
uint8_t lcdinit[16] = {76, 67, 68, 0, 82, 101, 97, 100, 121, 33, 0, 0, 0, 0, 0, 0};				// String: "LCD Ready!"
uint8_t usbinit[16] = {85, 83, 66, 0, 82, 101, 97, 100, 121, 33, 0, 0, 0, 0, 0, 0};		// Test string: "USB Ready!"

int main(void)
{
	// Lights and fan initialization
	set_output(DDRD,7);
	set_high(PORTD,7);

	// LCD initialization
	_delay_ms(200);
	CHA_LCDinit();
	CHA_LCDclr();
	CHB_LCDinit();
	CHB_LCDclr();
	CHA_LCDstringLine(lcdinit,0);

	// USB initialization
    wdt_enable(WDTO_1S); // enable 1s watchdog timer
    usbInit();
    usbDeviceDisconnect(); // enforce re-enumeration
	uchar i;
    for(i = 0; i<250; i++) { // wait 1000 ms
        wdt_reset(); // keep the watchdog happy
        _delay_ms(4);
    }
    usbDeviceConnect();
    sei(); // Enable interrupts after re-enumeration
    CHB_LCDstringLine(usbinit,0);

	// Feed watchdog and poll USB forever
    while(1) {
        wdt_reset();
        usbPoll();
    }

	return 0;
}

// Automagically called upon receiving a USB control message
USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data; // cast data to correct type
	uchar outputID;
	int cmdID;
	outputID = (rq->bRequest);
	cmdID = (rq->wValue.bytes[0]);

	if (outputID==0)
		set_low(PORTD,7);
	else if(outputID==1)
		set_high(PORTD,7);
	else if(outputID==2){
		CHA_LCDclr();
		CHB_LCDclr();
	} else if(outputID==10){
		// Expecting a string! Clear buffer and set index.
		addr = 0;
	} else if(outputID==11){
		// Got a char. Store it in the buffer.
		buff[addr] = cmdID;
		addr++;
	}

	// For the rest, we finished receiving the string; post it to proper line.
	else if(outputID==6)
		CHA_LCDstringLine(buff,0);
	else if(outputID==7)
		CHA_LCDstringLine(buff,1);
	else if(outputID==8)
		CHB_LCDstringLine(buff,0);
	else if (outputID==9)
		CHB_LCDstringLine(buff,1);

	return 0;
}
