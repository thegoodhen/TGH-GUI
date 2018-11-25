
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
		USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);//Taken from the WebSockets library... prevents bricking when you accidentally cause an excpetion; 
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


	TabbedPane* tp = new TabbedPane("tp1");//We first need to create a tabbed pane in order to add tabs!
	gui.add(tp);//We need to attach it to the GUI
	Tab* tab1 = new Tab("The first tab");//We create the first tab
	tp->addTab(tab1);//We add the tab to the tabPane
	Heading* h1 = new Heading("h1", 1, "Some content");//We create some heading
	Text* t = new Text("t1", "There is this text on the first tab... ");//We create some text
	Checkbox* c = new Checkbox("cb1", "Some random checkbox, which does nothing...");//We create some checkbox
	//We add the created elements into the first tab
	tab1->add(h1);
	tab1->add(t);
	tab1->add(c);
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


	Tab* tab3 = new Tab("More complex tab");
	tp->addTab(tab3);//Again, we add it to the tabPane
	//We create some more elelents for the second tab...
	Heading* h3 = new Heading("h3;", 1, "Complex example");
	Text* t3 = new Text("t3", "This is a bit more complex example!");
	hBox* hb1 = new hBox("hbox1");
	vBox* vb1 = new vBox("vbox1");
	vBox* vb2 = new vBox("vbox2");

	tab3->add(h3);
	tab3->add(t3);

	tab3->add(hb1);
	hb1->add(vb1);
	hb1->add(vb2);
	
	TabbedPane* tp2 = new TabbedPane("tp2");

	vb1->add(tp2);

	Text* t4 = new Text("t4", "This text is located in a vertical box.");
	vb2->add(t4);

	Tab* tab4 = new Tab("some inner tab");
	Tab* tab5 = new Tab("tab5", "some inner tab");
	tp2->add(tab4);
	tp2->add(tab5);

	Heading* h4 = new Heading("h4", 1, "Some more content in the inner tab...");
	Heading* h5 = new Heading("h5", 1, "And yet some more stuff");
	tab4->add(h4);
	tab5->add(h5);



}


void loop() {
	gui.loop();//you have to call this function in loop() for this library to work!
}

