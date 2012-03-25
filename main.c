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

// Debug
uint8_t rcvd[16] = {82, 101, 99, 105, 101, 118, 101, 100, 33, 0, 0, 0, 0, 0, 0, 0};				// Test string: "Recieved!"
uint8_t init[16] = {87, 97, 105, 116, 105, 110, 103, 46, 46, 46, 46, 46, 46, 46, 46, 46};		// Test string: "Waiting......"

int main(void)
{
	// LCD initialization
	_delay_ms(500); 		// Wait for power fluctuations to clear
	CHA_LCDinit();			// init LCD bit, dual line, cursor right
	CHA_LCDclr();			// clears LCD
	CHB_LCDinit();			// init LCD bit, dual line, cursor right
	CHB_LCDclr();			// clears LCD

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

	CHA_LCDstringLine(init,rand() % 2);
	CHB_LCDstringLine(init,rand() % 2);

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

	if(outputID==1){
		CHA_LCDstringLine(rcvd,rand() % 2);
	}

	return 0;
}
