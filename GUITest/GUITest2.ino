
/*
 * WebSocketServer_LEDcontrol.ino
 *
 *  Created on: 26.11.2015
 *
 */

#include <WebSocketsClient.h>
#include <WebSockets.h>
#include "GUIElement.h"
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>
#include "GUI.h"

#include "Button.h"
#include "Label.h"

#include "ElementTypes.h"


ESP8266WiFiMulti WiFiMulti;
GUI gui;
Button b("kokon", "slepice", printText);


void printText(int clientNum)
{
	USE_SERIAL.println("gek gek");
}

void setup() {
	//USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);

	//USE_SERIAL.setDebugOutput(true);

	USE_SERIAL.println();
	USE_SERIAL.println();
	USE_SERIAL.println();

	for (uint8_t t = 4; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
		USE_SERIAL.flush();
		delay(1000);
	}

	WiFiMulti.addAP("TGH_network", "r0ut3rp@$$");

	while (WiFiMulti.run() != WL_CONNECTED) {
		delay(100);
	}
	USE_SERIAL.println("WiFi.localIP()");
	USE_SERIAL.println(WiFi.localIP());
	gui.begin();

	Button* c=new Button("kokon", "slepice", printTAContents);
	gui.addln(c);
	Label* l = new Label("lbl1", "label");
	gui.addln(l);
	TextArea* t = new TextArea("txt1", "some text");
	gui.addln(t);
	Slider* s = new Slider("sl1", "some slider");
	gui.addln(s);
	//s->onClick(displayNumber);//if both are enabled, esp crashes... why?!
	s->onInput(displayNumber);

	s->setSynced(true);

	Checkbox* ch = new Checkbox("cb1", "some checkbox");
	gui.addln(ch);
	ch->onClick(displayNumber);
	ch->setSynced(true);

}


void loop() {
	static unsigned long lastMillis;
	gui.loop();
	if (millis() > lastMillis + 100)
	{
		lastMillis = millis();
		//gui.sendText("kdak kdak kokodak");
		if (gui.find("slepice") == NULL)
		{
			//Serial.println("pozor, je to null");
		}
		//gui.find("kokon")->setText((String)"kokon" + (lastMillis / 1000));
		String test;

		//std::function<void(void)> f = std::bind(&HardwareSerial::println, (HardwareSerial)Serial);
		//gui.find("kokon")->retreiveText(printSerial);
		//while (test == "");
		//gui.find("lbl1")->setText(ALL_CLIENTS, (String)analogRead(A0));
		//gui.find("sl1")->setProperty(ALL_CLIENTS, "value", (String)analogRead(A0));

		//String s=gui.find("txt1")->retrieveProperty("value");


		//Serial.println(s);
	}
}

void printSerial(String s)
{
	Serial.println(s);
}

void displayNumber(int client, int i)
{
	Serial.println("i:");
	Serial.println(i);
}

void printTAContents(int clientNo)
{
		//gui.find("txt1")->retrieveProperty(printSerial, "value");
		//String s=gui.find("txt1")->retrieveProperty("value");
		int i = gui.find("sl1")->retrieveIntValue(clientNo);
		Serial.println(i);
}