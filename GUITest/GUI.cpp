


#include "GUI.h"
using namespace std::placeholders;  // For _1 in the bind call

ESP8266WebServer server(80);
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
	//this->getHTML();

 SPIFFS.begin();                           // Start the SPI Flash Files System
  
  server.onNotFound([]() {                              // If the client requests any URI
		if (!handleFileRead(server, server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });

		server.begin();

		// Add service to MDNS
		MDNS.addService("http", "tcp", 80);
		MDNS.addService("ws", "tcp", 81);

	}
	void GUI::loop()
	{
		this->msgInString = "";
		webSocket.loop();//handle the websocket events and what not
		server.handleClient();
		handleRequest();
	}


	void GUI::webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

		switch (type) {
		case WStype_DISCONNECTED:
			USE_SERIAL.printf("[%u] Disconnected!\n", num);
			break;
		case WStype_CONNECTED: {
			IPAddress ip = webSocket.remoteIP(num);
			USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

			// send message to client
			webSocket.sendTXT(num, "Connected");
		}
							   break;
		case WStype_TEXT:
			USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
			//StaticJsonBuffer<1000> jb;
			//JsonObject& obj = jb.parseObject(payload);
			//this->handleRequest(obj);
			this->msgInString = (char*)payload;
			this->clientNo = num;

			break;
		}

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
		return webSocket.sendTXT(clientNum,theText);
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
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
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
		server.sendContent(getHeader());
		server.sendContent(getScript());//TODO: move script to SPIFFS

		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			{
				//Serial.println(i);
				// the containers publish all their elements whenever we call their "sendHtml()"; therefore we only need to publish the elements that have no container
				//and the containers themselves.
				if(elements[i]->getContainer()==NULL) //|| elements[i]->getElementType()=="CONTAINER")
				{
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
<link rel="stylesheet" type="text/css" href="./generalElement.css">
<link rel="stylesheet" type="text/css" href="./slider.css">
<link rel="stylesheet" type="text/css" href="./switch.css">
<link rel="stylesheet" type="text/css" href="./button.css">
<link rel="stylesheet" type="text/css" href="./textInput.css">
<link rel="stylesheet" type="text/css" href="./hBox.css">
<link rel="stylesheet" type="text/css" href="./vBox.css">
<link rel="stylesheet" type="text/css" href="./text.css">
)";
	}
	String GUI::getFooter()
	{
		return "</html> \n";
	}

	String GUI::getScript()
	{
		return R"(<head>
<script>
var theSocket = new WebSocket("ws://"+location.hostname+":81", ['arduino']);

function sendJSON(theJSON)
{
  theSocket.send(JSON.stringify(theJSON));
}

theSocket.onmessage = function (event) {
  var msg=JSON.parse(event.data);
  switch(msg.type)
  {
	case "setText":
		document.getElementById(msg.id).innerHTML = msg.newText;		
	break;
	case "getText":
		sendJSON({type: "response", id: msg.id, subType: "getText", text: document.getElementById(msg.id).innerHTML});
		break;
	case "getProperty":
		sendJSON({type: "response", id: msg.id, subType: "getProperty", propertyName: msg.propertyName, value: document.getElementById(msg.id)[msg.propertyName]});
		break;
	case "setProperty":
		if(msg.value=="false")//do we want to do it like this actually?
		{
			msg.value=false;
		}
		if(msg.value=="true")//do we want to do it like this actually?
		{
			msg.value=true;
		}
		document.getElementById(msg.id)[msg.propertyName]=msg.value;
		break;
	default:
		console.log("got invalid request");
	break;

  }
}
</script>
</head>)";
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
			//Serial.println("je to event");
			String id = obj["id"];
			GUIElement* ge = find(id);
			if (ge != NULL)
			{
			//Serial.println("neni to null");
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
