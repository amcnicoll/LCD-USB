***/ Summary /***

This code is for the LCD-USB project, which is a personal project aimed at producing two USB-controlled LCD readouts for displaying information on the outside of a computer case. It consists of the Windows USB driver, the Windows communication binary (called the "control utility") and the AVR code.

The free V-USB library (http://www.obdev.at/products/vusb/index.html) is used for USB communications from our AVR; this is paired with libusb (http://www.libusb.org/) on Windows, which gives access to useful USB functions through C. The library used for LCD control on the AVR is a very heavily modified version of one from Scienceprog.com; it has little functionality beyond what we need, and supports two completely independent channels. The rest of the code is original and is more or less up for grabs until we settle on some sort of license...

***/ User commands sent via control utility /***

#define LCD_OFF 0		// Turn backlights off
#define LCD_ON 	1		// Turn backlights on
#define LCD_CLR 2		// Clear both screens
#define FAN1 	3		// Control fan channel 1. Follow by value from 0-255 representing speed.
#define FAN2	4		// Control fan channel 2. Follow by value from 0-255 representing speed.
#define LIGHTS  5		// Control lights. Follow by value from 0-255 representing brightness.
#define LCDALN0 6		// Send string to first line on A. Follow precisely, then encoded string (see "Encoding")
#define LCDALN1 7		// Send string to second line on A. Follow precisely, then encoded string (see "Encoding")	
#define LCDBLN0 8		// Send string to first line on B. Follow precisely, then encoded string (see "Encoding")
#define LCDBLN1 9		// Send string to second line on B. Follow precisely, then encoded string (see "Encoding")

***/ Encoding /***

Strings sent to the control utility are send as expected, with two important exceptions:
- Special characters can be accessed with the escape character "~" followed by a number, corresponding to:
	0: Space
	1-5: Progress blocks from 1/5 to full
	6: Left bookend (progress bar border)
	7: Right bookend 
- No spaces may be sent; this marks the string as another argument. Instead use "~0".

TODO
- General robustness on control util input