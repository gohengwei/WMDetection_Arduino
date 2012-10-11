/*
 i2cLCD.h - Library for controlling a SparkFun i2cLCD module
	    Code written for firmware version 2.5
*/
#ifndef i2cLCD_h
#define i2cLCD_h

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds,digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

//#include "WConstants.h"

// Commands
#define LCD_BACKLIGHTON		0x13
#define LCD_BACKLIGHTOFF	0x14
#define LCD_CLEARDISPLAY	0x0C
#define LCD_CURSORSHIFT		0x10
#define LCD_DISPLAYCONTROL	0x08
#define LCD_ENTRYMODESET	0x04
#define LCD_FUNCTIONSET		0x20
#define LCD_SETCGRAMADDR	0x40
#define LCD_SETDDRAMADDR	0x80
#define LCD_SETSPLASHSCREEN	0x0A
#define LCD_SPLASHTOGGLE	0x09
#define LCD_RETURNHOME		0x01
#define LCD_CARRIAGERETURN	0x0D


// Flags for display entry mode
#define LCD_ENTRYRIGHT		0x00
#define LCD_ENTRYLEFT		0x02

// Flags for display on/off control
#define LCD_BLINKON		0x06
#define LCD_UNDERLINEON		0x05
#define LCD_CURSOROFF		0x04

class i2cLCD : public Print {
public:
	i2cLCD (int pin);

	void begin();
	void clear();
	void home();
	void setBrightness(bool);
	//void print(char*);
	virtual size_t write(uint8_t);
	void println();
	void setSplash();
	void toggleSplash();

	void setCursor(uint8_t);
	void display();
	void noDisplay();

	void setCursor(uint8_t, uint8_t);

	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();

	void createChar(int, uint8_t[]);

private:
	void command(uint8_t);
	void specialCommand(uint8_t);

	uint8_t _addr;

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;
	uint8_t _numlines;
	uint8_t _numchars;
	uint8_t _rowoffset;
};

#endif