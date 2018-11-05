
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


ESP8266WiFiMulti WiFiMulti;
GUI gui;
Button b("kokon", "slepice", printText);


void printText()
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
	gui.add(&b);

}


void loop() {
	gui.loop();
}
