
/*
 * WebSocketServer_LEDcontrol.ino
 *
 *  Created on: 26.11.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "TGH_GUI.h"//We include the library



ESP8266WiFiMulti WiFiMulti;//for connecting to a router
GUI gui;


void setup() {
	//USE_SERIAL.begin(921600);
	USE_SERIAL.begin(115200);//For debug output

	//USE_SERIAL.setDebugOutput(true);

	USE_SERIAL.println();
	USE_SERIAL.println();
	USE_SERIAL.println();

	for (uint8_t t = 3; t > 0; t--) {
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);//Taken from the WebSockets library, nice to properly connect to the serial port
		USE_SERIAL.flush();
		delay(1000);
	}

	WiFiMulti.addAP("TGH_network", "r0ut3rp@$$");

	while (WiFiMulti.run() != WL_CONNECTED) {//We wait till we connect to our router
		delay(100);
	}
	USE_SERIAL.println("WiFi.localIP()");//then we print out the IP of this device; paste it into the browser window to connect to it; alternatively, you could
	//also use an AP mode, where the device has its own SSID and password!
	USE_SERIAL.println(WiFi.localIP());
	gui.begin();//this is a necessary call! You need to call this in setup() to properly initialize the GUI!!

	//First, we create a new horizontal box - all items in this box will be centered around the middle and will fit side-by-side,
	//as long as the screen width of the target device permits that. We do this just to center the content on screen now!
	hBox* hb = new hBox("hBox");
	gui.add(hb);//We add it to the user interface (otherwise it wouldn't be visible anywhere!)
	vBox* vb = new vBox("vBox");//we create a new vertical box - the things in this box will go one under another
	hb->add(vb);//we add the vertical box inside the horizontal box we created

	Heading* h = new Heading("heading1", 1, "Print analog value");//We create heading of level "1", name it "heading1" and change its text to "Print analog value".
	vb->add(h);//Always remember to actually add the elements somewhere!
	Text* t = new Text("text1", R"(This example reads the value on input A0 using analogRead(A0) and then
displays it on a label element; connect a slider of a potentiometer to A0 and the other wires
to 3.3V and ground and move the potentiometer to see the results!)");//We add some explanation
	vb->add(t);
	Label* l = new Label("lbl1", "The analog reading: ");
	vb->add(l);
}


void loop() {
	gui.loop();//you have to call this function in loop() for this library to work!
	String val = (String)analogRead(A0);//When we want to set the text of some label, we need to have a String. This is how we get it!
	//Serial.println(val);
	//Will see the same value; alternatively, you could specify which clients should see the value 
	GUIElement* ge = gui.find("lbl1");
	ge->setText(ALL_CLIENTS, val);//set the text of the label to the reading... ALL_CLIENTS means that all devices connected to this Arduino thingy
	delay(10);
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
