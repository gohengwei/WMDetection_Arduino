/*
 i2cLCD.cpp - Library for controlling a i2cLCD
              module.
	      Code written for firmware version 2.5
*/
#include "Arduino.h"  
#include "i2cLCD.h"
#include "Wire.h"

//	PUBLIC FUNCTIONS

// Contstructor
// defaults to 16x2 display
i2cLCD::i2cLCD(int addr) {
	_addr = addr;
}

void i2cLCD::begin()
{
	Wire.begin();
}

// Set brightness value range 1-30 1=OFF 30=FULL
void i2cLCD::setBrightness(bool value){
	if(value)	command(LCD_BACKLIGHTON);
	else command(LCD_BACKLIGHTOFF);
}

// Clears screen and returns cursor to home position
void i2cLCD::clear(){
	Wire.beginTransmission(_addr);
	//Need to waste one byte first before data can be transmitted
	Wire.write(byte(0x00));
	//Wire.write(byte(0x45));
	Wire.write(byte(LCD_CLEARDISPLAY));
	Wire.endTransmission();
	
}

void i2cLCD::setCursor(uint8_t row, uint8_t col)
{
	Wire.beginTransmission(_addr);
	//Need to waste one byte first before data can be transmitted
	Wire.write(byte(0x00));
	Wire.write(byte(0x03));
	Wire.write(byte(row));
	Wire.write(byte(col));
	Wire.endTransmission();
}

inline size_t i2cLCD::write(uint8_t value) {
	command(value);
  return 1; // assume sucess
}

void i2cLCD::println()
{
	command(LCD_CARRIAGERETURN);
}


// returns cursor to home position
void i2cLCD::home(){
	Wire.beginTransmission(_addr);
	//Need to waste one byte first before data can be transmitted
	Wire.write(byte(0x00));
	Wire.write(byte(LCD_RETURNHOME));
	Wire.endTransmission();
}

// Saves first 2 lines of txt to splash screen memory
void i2cLCD::setSplash(){
	specialCommand(LCD_SETSPLASHSCREEN);
}

// Toggles splashscreen on and off
void i2cLCD::toggleSplash(){
	specialCommand(LCD_SPLASHTOGGLE);
}

//  This is for text that flows Left to Right
void i2cLCD::leftToRight(){
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void i2cLCD::rightToLeft() {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Underline cursor on/off
void i2cLCD::setCursor(uint8_t cursor){
	switch(cursor)
	{
	case LCD_BLINKON :
		command(LCD_BLINKON);
		break;
	case LCD_CURSOROFF:
		command(LCD_CURSOROFF);
		break;
	case LCD_UNDERLINEON:
		command(LCD_UNDERLINEON);
		break;
	default:
		break;
	}
}

// Creates custom characters 8 char limit
// Input values start with 1
void i2cLCD::createChar(int location, uint8_t charmap[]){
	location -= 1;
	location &= 0x07;
  for (int i=0; i<8; i++){
    command(LCD_SETCGRAMADDR | (location << 3) | i);
  }
}

// PRIVATE FUNCTIONS

// Functions for sending the special command values
void i2cLCD::command(uint8_t value){
	Wire.beginTransmission(_addr);
	//Need to waste one byte first before data can be transmitted
	Wire.write(byte(0x00));
	Wire.write(byte(value));
	Wire.endTransmission();
	delay(5);
}
void i2cLCD::specialCommand(uint8_t value){
	delay(5);
}