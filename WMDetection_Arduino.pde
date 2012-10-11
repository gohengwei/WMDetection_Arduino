#include <i2cLCD.h>
#include <XBee.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Servo.h>

//Constants
#define LED_IND A1

//Xbee Set up
uint8_t payload[] = {4};
XBee xbee_t;
XBee xbee_m;
XBee xbee_d;
Rx16Response rx16_t = Rx16Response();
Rx16Response rx16_m = Rx16Response();
Rx16Response rx16_d = Rx16Response();

//Other sensors, LCD and SD set up
i2cLCD lcd(227);

//Variables to be used
int rssi;
static int ave;

void setup()
{

  /* add setup code here */
	//Initialize various hardware
	lcd.begin();

	//Initialize Arduino Serial Ports
	Serial.begin(115200);
	Serial1.begin(9600);
	Serial2.begin(9600);
	Serial3.begin(9600);
	
	//Initialize Xbees
	xbee_t.setSerial(Serial1);
	xbee_m.setSerial(Serial2);
	xbee_d.setSerial(Serial3);

	pinMode(LED_IND,OUTPUT);
	delay(500);
	lcd.clear();
	lcd.print("System Initialized");
	delay(500);
	lcd.clear();
	lcd.setCursor(1,1);
	lcd.print("System running");
	lcd.setCursor(2,1);
	lcd.print("XB TOP:");
	lcd.setCursor(3,1);
	lcd.print("XB MID:");
	lcd.setCursor(4,1);
	lcd.print("XB BOT:");

}

void loop()
{
	collectData();

}

void collectData()
{
	xbee_t.readPacket(20) ;
	if (xbee_t.getResponse().isAvailable()) {
		if (xbee_t.getResponse().getApiId() == RX_16_RESPONSE) {
            xbee_t.getResponse().getRx16Response(rx16_t);
			rssi = rx16_t.getRssi();
			Serial.print(millis() - ave);
			ave =millis();
			Serial.print(" ");
			Serial.print(rssi);
			lcd.setCursor(2,8);
			lcd.print(rssi);
		}
	} else Serial.print("*");

	Serial.print(" ");
	xbee_m.readPacket(20);
	//Middle XBees
	if (xbee_m.getResponse().isAvailable()) {
		if (xbee_m.getResponse().getApiId() == RX_16_RESPONSE) {
            xbee_m.getResponse().getRx16Response(rx16_m);
			rssi = rx16_m.getRssi();
			lcd.setCursor(3,8);
			Serial.print(millis() - ave);
			ave =millis();
			Serial.print(" ");
			Serial.print(rssi);
			lcd.print(rssi);			
		}
	} else Serial.print("*");
	
	Serial.print(" ");
	xbee_d.readPacket(20);
	if (xbee_d.getResponse().isAvailable()) {
		if (xbee_d.getResponse().getApiId() == RX_16_RESPONSE) {
            xbee_d.getResponse().getRx16Response(rx16_d);
			rssi = rx16_d.getRssi();
			Serial.print(millis() - ave);
			ave =millis();
			Serial.print(" ");
			Serial.print(rssi);
			lcd.setCursor(4,8);
			lcd.print(rssi);
		}
	} else Serial.print("*");

	//delay(1);
	Serial.println();
}

