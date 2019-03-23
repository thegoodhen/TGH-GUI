// TabbedPane.h

#pragma once
#include "Container.h"
#include "Tab.h"
#include "WebServerIncludes.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Container;
class Tab;


class TabbedPane: public Container
{
	
public:
	TabbedPane(String _id, String _text="");
	void addTab(Tab* t);
	void sendHtml(ESPWebServer & server) override;
	void add(GUIElement* ge) = delete;
	void add(Tab* t);
	
};
