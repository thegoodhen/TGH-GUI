/*
 * WebSocketServer_LEDcontrol.ino
 *
 *  Created on: 26.11.2015
 *
 */

#include "Tab.h"
#include "TabbedPane.h"
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






	//<<<<<<<<ACTUAL EXAMPLE - SPECIFIC CODE BEGINS HERE>>>>>>>>
	//----------------------------------------------------------
	//----------------------------------------------------------

	//First, we create a new horizontal box - all items in this box will be centered around the middle and will fit side-by-side,
	//as long as the screen width of the target device permits that. We do this just to center the content on screen now!
	hBox* hb = new hBox("hBox");
	gui.add(hb);//We add it to the user interface (otherwise it wouldn't be visible anywhere!)
	vBox* vb = new vBox("vBox");//we create a new vertical box - the things in this box will go one under another
	hb->add(vb);//we add the vertical box inside the horizontal box we created

	Heading* h = new Heading("heading1", 1, "Simple form example");//We create heading of level "1", name it "heading1" and change its text.
	vb->add(h);//Always remember to actually add the elements somewhere!
	Text* t = new Text("text1", R"(In this example, we demonstrate a simple form that gets submitted when the "Submit" button is clicked. See serial output!)");//We add some explanation
	vb->add(t);

	TextInput* ti = new TextInput("ti1", "First text input: ");
	vb->add(ti);

	TextInput* ti2 = new TextInput("ti2", "Second text input: ");
	vb->add(ti2);

	Checkbox* ch = new Checkbox("cb1", "Some checkbox: ");
	vb->add(ch);

	Slider* s = new Slider("sl1", "Some slider: ");
	vb->add(s);

	ListBox* lb = new ListBox("lb1", "some ListBox:");
	lb->addItem(new ListItem("Some first item"));
	lb->addItem(new ListItem("A second item"));
	lb->addItem(new ListItem("And yet another (third) item!"));
	vb->add(lb);

	Button* b = new Button("btn", "Submit", buttonCB);
	vb->add(b);


}


void loop() {
	gui.loop();//you have to call this function in loop() for this library to work!
}

void buttonCB(int user)
{
	USE_SERIAL.println("User clicked the button! User number: ");
	USE_SERIAL.println(user);
	USE_SERIAL.println("First text input:");
	USE_SERIAL.println(gui.find("ti1")->retrieveText(user));
	USE_SERIAL.println("Second text input:");
	USE_SERIAL.println(gui.find("ti2")->retrieveText(user));
	USE_SERIAL.println("Checkbox:");
	USE_SERIAL.println(gui.find("cb1")->retrieveIntValue(user));
	USE_SERIAL.println("Slider:");
	USE_SERIAL.println(gui.find("sl1")->retrieveIntValue(user));
	USE_SERIAL.println("ListBox");
	USE_SERIAL.println(gui.find("lb1")->retrieveText(user));
	USE_SERIAL.println(gui.find("lb1")->retrieveIntValue(user));
}
void lbCb(int user, ListItem li)
{
	USE_SERIAL.println(li.getValue());
}
