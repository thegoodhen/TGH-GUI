// Container.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ESP8266WebServer.h>
#include "GUIElement.h"

class Container : public GUIElement
{
public:
	virtual void openContainer(ESP8266WebServer& server);
	virtual void closeContainer(ESP8266WebServer& server);
	virtual void sendHtml(ESP8266WebServer& server) override;
	void sendContainerItemsHtml(ESP8266WebServer& server);
	void add(GUIElement* ge);
	GUIElement * find(String s);
	String getElementType() override;

private:
	std::vector<GUIElement*> elements;
};
