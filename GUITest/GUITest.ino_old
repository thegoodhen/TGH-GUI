/*
 Name:		GUITest.ino
 Created:	4.11.2018 17:00:49
 Author:	thegoodhen
*/
#include "Button.hpp"
#include "ArduinoJson.h"

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	Button b = Button("slepice", "slepice", testPrint);
	StaticJsonBuffer<1000> jb;
	char* input = "{\"id\":\"kokon\",\"evType\":\"click\"}";
	JsonObject& obj = jb.parseObject(input);
	delay(500);
	if (!obj.success())
	{
		Serial.println("Fail.");
	}
	b.handleEvent(obj);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}

void testPrint()
{
	Serial.print("gek gek");
}
