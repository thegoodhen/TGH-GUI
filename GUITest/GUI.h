// 
// 
// 



#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "GUIElement.h"
#include <vector>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>

#include <WebSocketsServer.h>
#define USE_SERIAL Serial



class GUIElement;

class GUI
{
public:
	GUI();
	void begin();
	void loop();

	void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
	


	

	/**
	Send the text out using Websockets
	*/
	int sendText(String theText);
	
	int sendText(int clientNum, String theText);

	int sendTextToAllBut(int clientNum, String theText);

	String getHTML();
	

	void sendHTML();

	String getHeader();
	
	String getFooter();
	

	String getScript();
	

	void addln(GUIElement * ge);

	void add(GUIElement*  ge);
	
	GUIElement* find(String s);
	

	int handleRequest();

	int handleRequest(int clNum, JsonObject & obj);

	//int handleRequest(JsonObject& obj);
	

private:
	std::vector<GUIElement*> elements;
	String msgInString = "";//String for storing the incoming messages
	int clientNo = 0;
};
