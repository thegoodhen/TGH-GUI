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
#include "Container.h"
#include <vector>
#include "WebServerIncludes.h"

#ifdef ESP8266
#include <ESP8266mDNS.h>
#include <Hash.h>
#else
#include <ESPmDNS.h>
#include <WiFiClientSecure.h>
#endif

#include <WebSocketsServer.h>
#include "SpiffsUtils.h"
#define USE_SERIAL Serial
#define ALL_CLIENTS -1



class GUIElement;

class GUI
{
public:
	GUI();
	void begin();
	void loop();

	void sendInitializations(int clientNo);

	void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

	void sendDeviceInfo();
	


	

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
	std::vector<GUIElement*>* getElements();

	void showInfo(int userNo, String text);


	void showError(int userNo, String text);//show a toast popup in the browser
	

private:
	void showToast(int userNo, String text, String toastType);
	std::vector<GUIElement*> elements;
	String msgInString = "";//String for storing the incoming messages
	int clientNo = 0;
};
