***/ Summary /***

This code is for the LCD-USB project, which is a personal project aimed at producing two USB-controlled LCD readouts for displaying information on the outside of a computer case. It consists of the Windows USB driver, the Windows communication binary (called the "control utility") and the AVR code.

The free V-USB library (http://www.obdev.at/products/vusb/index.html) is used for USB communications from our AVR; this is paired with libusb (http://www.libusb.org/) on Windows, which gives access to useful USB functions through C. The library used for LCD control on the AVR is a very heavily modified version of one from Scienceprog.com; it has little functionality beyond what we need, and supports two completely independent channels. The rest of the code is original and is more or less up for grabs until we settle on some sort of license...

EAGLE files for the corresponding board can be found under "board." As this project wraps up I'll post a BOM and assembly pictures. The SVG is meant for use in a laser cutter; I spray-paint copper-clad boards and engrave away the trace patterns, and etch what's left. You can also invert the SVG and use the more traditional laser printer style, although its complexity might lead to some headaches.

***/ Control Utility Usage /***

Note that all of these functions can be accessed using the include gui.exe, and that you must install the Windows driver to use this device at all.

usblcd.exe [COMMAND] [ARGUMENT]

Commands:
0		// Turn backlights off
1		// Turn backlights on
2		// Clear both screens
3 [0-255]	// Control fan channel 1. Follow by value from 0-255 representing speed.
4 [0-255]	// Control fan channel 2. Follow by value from 0-255 representing speed.
5 [0-255]	// Control lights. Follow by value from 0-255 representing brightness.
6 [String]	// Send string to first line on A. Argument is encoded string.
7 [String]	// Send string to second line on A. Argument is encoded string.	
8 [String]	// Send string to first line on B. Argument is encoded string.
9 [String]	// Send string to second line on B. Argument is encoded string.

***/ Encoding /***

Strings sent to the control utility are send as expected, with two important exceptions:
- Special characters can be accessed with the escape character "~" followed by a number, corresponding to:
	0: Space
	1-5: Progress blocks from 1/5 to full
	6: Left bookend (progress bar border)
	7: Right bookend 
- No spaces may be sent included; this splits the string up into multiple arguments. Instead use "~0".

TODO
- General robustness on control util input