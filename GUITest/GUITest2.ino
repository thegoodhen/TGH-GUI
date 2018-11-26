
/*
 * WebSocketServer_LEDcontrol.ino
 *
 *  Created on: 26.11.2015
 *
 */

#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
typedef  ESP8266WiFiMulti WiFiMulti;
#else
#include <WiFi.h>
#include <WiFiMulti.h>
#endif

#include <WiFiClientSecure.h>
#include "TGH_GUI.h"//We include the library



WiFiMulti wiFiMulti;//for connecting to a router
GUI gui;


void setup() {
	//USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);//For debug output

	//USE_SERIAL.setDebugOutput(true);

	USE_SERIAL.println();
	USE_SERIAL.println();
	USE_SERIAL.println();

	for (uint8_t t = 3; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);//Taken from the WebSockets library... prevents bricking when you accidentally cause an excpetion; 
		USE_SERIAL.flush();
		delay(1000);
	}

	wiFiMulti.addAP("TGH_network", "r0ut3rp@$$");

	while (wiFiMulti.run() != WL_CONNECTED) {//We wait till we connect to our router
		delay(100);
	}
	USE_SERIAL.println("WiFi.localIP()");//then we print out the IP of this device; paste it into the browser window to connect to it; alternatively, you could
	//also use an AP mode, where the device has its own SSID and password!
	USE_SERIAL.println(WiFi.localIP());
	gui.begin();//this is a necessary call! You need to call this in setup() to properly initialize the GUI!!






	//<<<<<<<<ACTUAL EXAMPLE - SPECIFIC CODE BEGINS HERE>>>>>>>>
	//----------------------------------------------------------
	//----------------------------------------------------------


	TabbedPane* tp = new TabbedPane("tp1");//We first need to create a tabbed pane in order to add tabs!
	Tab* tab1 = new Tab("The first tab");//We create the first tab
	Heading* h1 = new Heading("h1", 1, "Some content");//We create some heading
	Text* t = new Text("t1", "There is this text on the first tab... ");//We create some text
	Checkbox* c = new Checkbox("cb1", "Some random checkbox, which does nothing...");//We create some checkbox
	//We add the created elements into the first tab
	tab1->add(h1);
	tab1->add(t);
	tab1->add(c);
	gui.add(tp);//We need to attach it to the GUI
	tp->addTab(tab1);//We add the tab to the tabPane
	//We create the second tab
	Tab* tab2 = new Tab("The second tab");
	tp->addTab(tab2);//Again, we add it to the tabPane
	//We create some more elelents for the second tab...
	Heading* h2 = new Heading("h2", 1, "Some more content");
	Text* t2 = new Text("t2", "Now we have some other text on the second tab... ");
	Slider* s = new Slider("s1", "Some random slider which doesn't do much, either...");
	//...and we add them to the second tab
	tab2->add(h2);
	tab2->add(t2);
	tab2->add(s);




}


void loop() {
	gui.loop();//you have to call this function in loop() for this library to work!
}

