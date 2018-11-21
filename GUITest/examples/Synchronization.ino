
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






	//<<<<<<<<ACTUAL EXAMPLE - SPECIFIC CODE BEGINS HERE>>>>>>>>
	//----------------------------------------------------------
	//----------------------------------------------------------

	//First, we create a new horizontal box - all items in this box will be centered around the middle and will fit side-by-side,
	//as long as the screen width of the target device permits that. We do this just to center the content on screen now!
	hBox* hb = new hBox("hBox");
	gui.add(hb);//We add it to the user interface (otherwise it wouldn't be visible anywhere!)
	vBox* vb = new vBox("vBox");//we create a new vertical box - the things in this box will go one under another
	hb->add(vb);//we add the vertical box inside the horizontal box we created

	Heading* h = new Heading("heading1", 1, "Synchronization example");//We create heading of level "1", name it "heading1" and change its text.
	vb->add(h);//Always remember to actually add the elements somewhere!
	Text* t = new Text("text1", R"(In this example we show the difference between a synchronized GUI element,
 a non-synchronized one and also point out the issue of 
synchronizing elements with no events!
<b>To see this effect, please either connect from multiple devices, or open this site in multiple tabs!</b>)");//We add some explanation
	vb->add(t);

	//the state of the following checkbox can be different for each client!
	Checkbox* ch = new Checkbox("cb1", "A non-synced checkbox", nonSyncedCheckboxCallback);
	ch->setSynced(false);//default in the current API, but possible subject to change!
	vb->add(ch);

	//the state of the following checkbox is always synchronized (=the same) for each client!
	Checkbox* ch2 = new Checkbox("cb2", "A synced checkbox", syncedCheckboxCallback);
	ch2->setSynced(true);//TODO: check if there is a copy???? because it acts weird!
	vb->add(ch2);

	//The synchronization occurs when the Arduino learns about the state of the element. This happens when an event is fired
	//or when you read the given property of the element manually (TODO: IMPLEMENT THE LATTER!)
	//This gives you some degree of control over when the synchronization happens. However, observe that if you specify no
	//callbacks and don't poll the value manually, the synchronization never really takes place!
	Checkbox* ch3 = new Checkbox("cb3", "An (incorrectly!) synced checkbox");
	vb->add(ch3);

	Slider* s = new Slider("sl1", "Sliders can be synchronized too! ");
	s->setSynced(true);
    //A workaround to the previously mentioned issue is to specify some dummy callback function which actually does nothing as such:
	s->onInput(dummySliderCallback);
	vb->add(s);

}


void loop() {
	gui.loop();//you have to call this function in loop() for this library to work!
}


void nonSyncedCheckboxCallback(int user, boolean state)
{
	USE_SERIAL.println((String)"user number " + user + (String)" changed the state of (their!) checkbox to " + state);
}

void syncedCheckboxCallback(int user, boolean state)
{
	USE_SERIAL.println((String)"user number " + user + (String)" changed the global state of  checkbox to " + state);
}

void dummySliderCallback(int user, int value)
{
	//do nothing
}
