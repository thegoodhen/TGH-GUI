// Tab.h
#pragma once
#include "ESP8266WebServer.h"
#include "Container.h"



#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class Tab : public Container
{
public:
	Tab(String _id, String _text="");
	void sendHeaderHtml(ESP8266WebServer& server);
	void openContainer(ESP8266WebServer & server) override;
};
