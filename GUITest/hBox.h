// hBox.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <ESP8266WebServer.h>
#include "Container.h"

class hBox :public Container
{
public:
	hBox(String _id);
	void openContainer(ESP8266WebServer& server) override;
};
