// Container.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "WebServerIncludes.h"
#include "GUIElement.h"


class Container : public GUIElement
{
public:
	virtual void openContainer(ESPWebServer& server);
	virtual void closeContainer(ESPWebServer& server);
	virtual void sendHtml(ESPWebServer& server) override;
	void sendContainerItemsHtml(ESPWebServer& server);
	void sendInitialization(int clientNo) override;
	void add(GUIElement* ge);
	GUIElement * find(String s);
	String getElementType() override;

protected:
	std::vector<GUIElement*> elements;
};
