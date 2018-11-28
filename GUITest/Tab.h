// Tab.h
#pragma once
#include "WebServerIncludes.h"
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
	void sendHeaderHtml(ESPWebServer& server);
	void openContainer(ESPWebServer & server) override;
};
