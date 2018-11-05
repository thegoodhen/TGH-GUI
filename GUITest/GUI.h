

#pragma once
#include "GUIElement.hpp"
#include <vector>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>
#define USE_SERIAL Serial

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

class GUI
{
public:
	GUI()
	{

	}
	void begin()
	{
		// start webSocket server
		webSocket.begin();
		void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length);
		webSocket.onEvent(webSocketEvent);

		if (MDNS.begin("esp8266")) {
			USE_SERIAL.println("MDNS responder started");
		}

		// handle index
		server.on("/", []() {
			// send index.html
			//String getDatGTML();
			//sendText("gek");
			//int sendText(String text);
			String getHTML();
			server.send(200,"text/html",getHTML());
			//sendText(getHTML());
			//server.send(200, "text/html", "<html><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendRGB() {  var r = parseInt(document.getElementById('r').value).toString(16);  var g = parseInt(document.getElementById('g').value).toString(16);  var b = parseInt(document.getElementById('b').value).toString(16);  if(r.length < 2) { r = '0' + r; }   if(g.length < 2) { g = '0' + g; }   if(b.length < 2) { b = '0' + b; }   var rgb = '#'+r+g+b;    console.log('RGB: ' + rgb); connection.send(rgb); }</script></head><body>LED Control:<br/><br/>R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>G: <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>B: <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/></body></html>");
		});

		server.begin();

		// Add service to MDNS
		MDNS.addService("http", "tcp", 80);
		MDNS.addService("ws", "tcp", 81);

	}
	void loop()
	{
		webSocket.loop();
		server.handleClient();
	}


	void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

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
			break;
		}

	}

	/**
	Send the text out using Websockets
	*/
	int sendText(String theText)
	{
		webSocket.sendTXT(0,theText);//TODO: make sure this also works for other user than just the 0th.
		//server.send(200, "text/html", "<html><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendRGB() {  var r = parseInt(document.getElementById('r').value).toString(16);  var g = parseInt(document.getElementById('g').value).toString(16);  var b = parseInt(document.getElementById('b').value).toString(16);  if(r.length < 2) { r = '0' + r; }   if(g.length < 2) { g = '0' + g; }   if(b.length < 2) { b = '0' + b; }   var rgb = '#'+r+g+b;    console.log('RGB: ' + rgb); connection.send(rgb); }</script></head><body>LED Control:<br/><br/>R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>G: <input id=\"g\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/>B: <input id=\"b\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendRGB();\" /><br/></body></html>");
		//server.send(200, "text/html", theText);
		return 0;
	}
	String getHTML()
	{
		String returnString;
		returnString += getHeader();
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			{
				returnString += elements[i].getHTML();
			}
		}
		returnString += getFooter();
		return returnString;
	}

	String getHeader()
	{
		return "<!DOCTYPE html>\n\
<html>\n\
\n";
	}
	String getFooter()
	{
		return "</html> \n";
	}

	String getScript()
	{
		return " <head>\n\
<script>\n\
var theSocket = new WebSocket(\"ws://192.168.0.102:81\", [\'arduino\']);\n\
\n\
function sendJSON(theJSON)\n\
{\n\
  theSocket.send(JSON.stringify(theJSON));\n\
}\n\
\n\
theSocket.onmessage = function (event) {\n\
  console.log(event.data);\n\
}\n\
</script>\n\
</head>";
	}

	void add(GUIElement ge)
	{
		elements.push_back(ge);
		ge.setGUI(this);
	}
	GUIElement* find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i].getId() == s)
			{
				return &elements[i];
			}
		}
		return NULL;
	}

	int handleRequest(JsonObject obj)
	{
		if (strcmp(obj["type"], "event"))
		{
			String id = obj["evType"];
			GUIElement* ge = find(id);
			if (ge != NULL)
			{
				return ge->handleEvent(obj);
			}
			else
			{
				return 1;
			}
		}
		return 0;
	}

private:
	std::vector<GUIElement> elements;
};
