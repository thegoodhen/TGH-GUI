


#include "GUI.h"
//#define TGH_DEBUG kokon
using namespace std::placeholders;  // For _1 in the bind call

ESPWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

	GUI::GUI()
	{

	}
	void GUI::begin()
	{
		// start webSocket server
		webSocket.begin();
		//void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length);

	//std::function<void(uint8_t num, WStype_t type, uint8_t* payload, size_t length)> f1 = std::bind(&GUI::webSocketEvent, this);
	auto f1 = std::bind(&GUI::webSocketEvent, this, _1, _2, _3, _4);
		webSocket.onEvent(f1);

		if (MDNS.begin("esp8266")) {
			USE_SERIAL.println("MDNS responder started");
		}

		// handle index
		//void sendHTML(void);

		/*
    server.on("/", []() {
        // send index.html
        server.send(200, "text/html", "<html><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendRGB() {  var r = parseInt(document.getElementById('r').value).toString(16);  var g = parseInt(document.getElementById('g').value).toString(16);  var b = parseInt(document.getElementById('b').value).toString(16);  if(r.length < 2) { r = '0' + r; }   if(g.length < 2) { g = '0' + g; }   if(b.length < 2) { b = '0' + b; }   var rgb = '#'+r+g+b;    console.log('RGB: ' + rgb); connection.send(rgb); }</script></head><body>LED Control:<br/><br/>R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>G: <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>B: <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/></body></html>");
    });
	*/
		//server.on("/", [](GUI* const thisPtr)->void {thisPtr->sendHTML();}(this));
		//void getHTML(void);
    //auto fcn = std::mem_fn(GUI::getHTML);
	std::function<void(void)> f = std::bind(&GUI::sendHTML, this);
	server.on("/", f);
	std::function<void(void)> f2 = std::bind(&GUI::sendDeviceInfo, this);
	server.on("/deviceinfo", f2);

	//this->getHTML();

#ifdef ESP8266
 SPIFFS.begin();                           // Start the SPI Flash Files System
#else
	SPIFFS.begin(true);
#endif
  
  server.onNotFound([]() {                              // If the client requests any URI
		if (!handleFileRead(server, server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });

		server.begin();

		// Add service to MDNS
		//MDNS.addService("http", "tcp", 80);
		//MDNS.addService("ws", "tcp", 81);

	}
	void GUI::loop()
	{
		this->msgInString = "";
		webSocket.loop();//handle the websocket events and what not
		server.handleClient();
		handleRequest();
	}

	void GUI::sendInitializations(int clientNo)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			{
				//Serial.println(i);
				// the containers publish all their elements whenever we call their "sendHtml()"; therefore we only need to publish the elements that have no container
				//and the containers themselves.
				if(elements[i]->getContainer()==NULL) //|| elements[i]->getElementType()=="CONTAINER")
				{
					elements[i]->sendInitialization(clientNo);
				}
				//server.sendContent(elements[i]->getHTML());
				//returnString += elements[i]->getHTML();
			}
		}
	}

	void GUI::webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

		switch (type) {
		case WStype_DISCONNECTED:

			//#ifdef TGH_DEBUG
			USE_SERIAL.printf("[%u] Disconnected!\n", num);
			//#endif
			break;
		case WStype_CONNECTED: {
			IPAddress ip = webSocket.remoteIP(num);

			#ifdef TGH_DEBUG
				#pragma message "J� jsem asi slepice"
			USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
			#else
				#pragma message "J� nejsem v�bec slepice"
			#endif

			// send message to client
			sendInitializations(num);

			//webSocket.sendTXT(num, "Connected");
		}
							   break;
		case WStype_TEXT:

			#ifdef TGH_DEBUG
				USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
			#endif
			//StaticJsonBuffer<1000> jb;
			//JsonObject& obj = jb.parseObject(payload);
			//this->handleRequest(obj);
			this->msgInString = (char*)payload;
			this->clientNo = num;

			break;
		default:
			break;
		}

	}


	void GUI::sendDeviceInfo()
	{
		server.sendHeader("Expires", "-1");
		server.sendHeader("Access-Control-Allow-Origin", "*");
		server.setContentLength(CONTENT_LENGTH_UNKNOWN);
		// here begin chunked transfer
		//String returnString;

		server.send(200,"text/html","");

		StaticJsonBuffer<1000> jb;
		JsonObject& obj = jb.createObject();
		obj["name"] = "slepice";
		obj["version"] = "1.0.0";
		String theJson;
		obj.printTo(theJson);

		server.sendContent(theJson);

		server.sendContent("");//transfer done
		server.client().stop();
	}
	

	/**
	Send the text out using Websockets
	*/
	int GUI::sendText(int clientNum, String theText)
	{
		if (clientNum == ALL_CLIENTS)
		{
			return webSocket.broadcastTXT(theText);
		}
		return !webSocket.sendTXT(clientNum,theText);
		//server.send(200, "text/html", "<html><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendRGB() {  var r = parseInt(document.getElementById('r').value).toString(16);  var g = parseInt(document.getElementById('g').value).toString(16);  var b = parseInt(document.getElementById('b').value).toString(16);  if(r.length < 2) { r = '0' + r; }   if(g.length < 2) { g = '0' + g; }   if(b.length < 2) { b = '0' + b; }   var rgb = '#'+r+g+b;    console.log('RGB: ' + rgb); connection.send(rgb); }</script></head><body>LED Control:<br/><br/>R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>G: <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>B: <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/></body></html>");
		//server.send(200, "text/html", theText);
		return 0;
	}

	int GUI::sendTextToAllBut(int clientNo, String theText)
	{
		boolean allGood = true;
		for (int i = 0;i < webSocket.connectedClients();i++)
		{
			if (i != clientNo)
			{
				Serial.println(theText);
				allGood=allGood|webSocket.sendTXT(i, theText);
			}
		}
		return allGood;
	}

	String GUI::getHTML()
	{
		String returnString;
		returnString += getHeader();
		returnString += getScript();
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {//TODO: wait, std::vector...int? wat
			{
				//Serial.println(i);
				returnString += elements[i]->getHTML();
			}
		}
		returnString += getFooter();
		return returnString;
	}

	void GUI::sendHTML()
	{
		//this code is taken from: https://www.esp8266.com/viewtopic.php?f=8&t=16830&start=4
		server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
		server.sendHeader("Pragma", "no-cache");
		server.sendHeader("Expires", "-1");
		server.setContentLength(CONTENT_LENGTH_UNKNOWN);
		// here begin chunked transfer
		//String returnString;

		server.send(200,"text/html","");
		Serial.println("sending header...");
		server.sendContent(getHeader());
		//server.sendContent(getScript());//TODO: move script to SPIFFS

		Serial.println("the number of elements is:");
		Serial.println(elements.size());
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			{
				//Serial.println(i);
				// the containers publish all their elements whenever we call their "sendHtml()"; therefore we only need to publish the elements that have no container
				//and the containers themselves.
				if(elements[i]->getContainer()==NULL) //|| elements[i]->getElementType()=="CONTAINER")
				{
					Serial.println("sendin some html, yall");
					elements[i]->sendHtml(server);
				}
				//server.sendContent(elements[i]->getHTML());
				//returnString += elements[i]->getHTML();
			}
		}

		server.sendContent(getFooter());
		server.sendContent("");//transfer done
		server.client().stop();
		//returnString += getFooter();
		//return returnString;
	}

	/*void GUI::sendHTML()
	{
		server.send(200,"text/html",getHTML());

	}*/

	String GUI::getHeader()
	{
		return R"(<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="stylesheet" type="text/css" href="./css.css">
<script src="./javaScript.js"></script>
<link rel="stylesheet" href="dygraph.css">
<script src="dygraph.min.js"></script>
<body onload='openSocket()'>
)";
	}
	String GUI::getFooter()
	{
		return "<div id=\"toast\"></div></body></html> \n";
	}

	String GUI::getScript()
	{
		return "slepice";//R"(<head></head>)";
	}

	void GUI::addln(GUIElement* ge)
	{
		this->add(ge);
		ge->setLineBreak(true);
	}

	void GUI::add(GUIElement* ge)
	{
		if (this->find(ge->getId()))//if already there, fail; TODO: change the return type to int to signal errors
		{
			return;
		}
		elements.push_back(ge);
		ge->setGUI(this);
	}

	/*
	GUIElement* GUI::find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i]->getId() == s)
			{
				return elements[i];
			}
		}
		return NULL;
	}
*/

	GUIElement* GUI::find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i]->getElementType() == "CONTAINER")
			{
				GUIElement* foundElement = ((Container*)elements[i])->find(s);
				if (foundElement!=NULL)//if the container found it
				{
					return foundElement;
				}
			}
			if (elements[i]->getId() == s)
			{
				return elements[i];
			}
		}
		return NULL;
	}

	int GUI::handleRequest()
	{
			StaticJsonBuffer<1000> jb;
			JsonObject& obj = jb.parseObject(msgInString);
			if (!obj.success())
			{
				return 1;
			}
			this->handleRequest(clientNo, obj);
			return 0;
	}
	int GUI::handleRequest(int clNum, JsonObject& obj)
	{
		if (strcmp(obj["type"], "event")==0)
		{
			//tghDbg(("je to event"));//PRO� NEFACH�?!!?	
			String id = obj["id"];
			GUIElement* ge = find(id);
			if (ge != NULL)
			{
				return ge->handleEvent(clNum, obj);
			}
			else
			{
				return 1;
			}
		}
		if (strcmp(obj["type"], "response")==0)
		{
			//Serial.println("lplp");
			//Serial.println("je to response");
			String id = obj["id"];
			GUIElement* ge = find(id);
			if (ge != NULL)
			{
				//Serial.println("neni to null");
				return ge->handleResponse(obj);
			}
			else
			{
				return 1;
			}
		}

		return 1;
	}

	std::vector<GUIElement*>* GUI::getElements()
	{
		return &(this->elements);
	}

	void GUI::showInfo(int userNo, String text)
	{
		this->showToast(userNo, text, "info");
	}

	void GUI::showError(int userNo, String text)
	{
		this->showToast(userNo, text, "error");
	}

	void GUI::showToast(int userNo, String text, String toastType)
	{

		StaticJsonBuffer<500> jb;
		JsonObject& obj = jb.createObject();
		obj["type"] = "showToast";
		obj["toastType"] = toastType;
		obj["text"] = text;
		String str;
		obj.printTo(str);
		this->sendText(userNo, str);
	}


