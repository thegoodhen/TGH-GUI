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
	void sendHtml(ESP8266WebServer& server) override;
	void add(GUIElement* ge);
	String getElementType() override;
};
