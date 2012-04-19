/*
 * Fan/light pins and communication commands here!
 * USB configuration (data pins, device ID) is in usbconfig.h
 * LCD configuration (pins, ports) is in lcd_lib_4bit.h
 *
 *  Created on: Apr 2, 2012
 *      Author: Anthony McNicoll
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// Pins
#define F1PIN	5
#define F2PIN	3
#define LPIN	6
#define BLPIN	7

// Ports
#define F1PORT	PORTD
#define F2PORT	PORTD
#define LPORT	PORTD
#define BLPORT	PORTD

// Data directions
#define F1DD	DDRD
#define F2DD	DDRD
#define LDD		DDRD
#define BLDD	DDRD

// Commands from control utility
#define BACKLIGHT_OFF	0
#define BACKLIGHT_ON	1
#define CLEAR			1
#define FAN1_SPEED		3
#define FAN2_SPEED		4
#define LIGHT_SPEED		5
#define POST_LINEA0		6
#define POST_LINEA1		7
#define POST_LINEB0		8
#define POST_LINEB1		9
#define INIT_TRANSMIT	10
#define RCV_CHAR		11

#endif /* CONFIG_H_ */
