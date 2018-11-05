#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"

class GUIElement
{
public:

	virtual int handleEvent(JsonObject& obj)
	{
		return 1;
	}
	virtual String getHTML()
	{
		return "";
	}
	String getId()
	{
		return id;
	}
protected:
	String id;
	String text;
};
