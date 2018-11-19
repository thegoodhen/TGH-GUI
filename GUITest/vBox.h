// vBox.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <ESP8266WebServer.h>
#include "Container.h"

class vBox :public Container
{
public:
	vBox(String _id);
	void openContainer(ESP8266WebServer& server) override;
};
