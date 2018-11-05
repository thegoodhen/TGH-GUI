// GUIElement.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Arduino.h"
#include <ArduinoJson.h>
#include "GUI.h"
class GUI;




class GUIElement
{
public:

	void setGUI(GUI* _gui);
	virtual int handleEvent(JsonObject& obj);
	virtual String getHTML();
	String getId();
	int setText(String theText);
protected:
	String id;
	String text;
	GUI* gui;
};
