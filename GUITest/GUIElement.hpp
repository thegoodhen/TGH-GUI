#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"
#include "GUI.h"
class GUI;

class GUIElement
{
public:

	void setGUI(GUI* _gui)
	{
		gui = _gui;
	}
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

	int setText(String theText)
	{
		DynamicJsonBuffer jb(theText.length() + 100);
		JsonObject& obj = jb.createObject();
		obj["type"] = "setText";
		obj["id"] = id;
		obj["newText"] = theText;
		String sentString;
		obj.printTo(sentString);
		gui->sendText(sentString);

	}
protected:
	String id;
	String text;
	GUI* gui;
};
