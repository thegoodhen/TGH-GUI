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
#include <functional>
class GUI;




class GUIElement
{
public:

	void setGUI(GUI* _gui);
	virtual int handleEvent(JsonObject& obj);
	int handleResponse(JsonObject & obj);
	virtual String getHTML();
	String getId();
	int setText(String theText);
	void retreiveText(std::function<void(String)> func);
	void retrieveProperty(std::function<void(String)> func, String propertyName);
	//void retreiveText(String * theText);
protected:
	String id;
	String text;
	String elementType = "div";
	String callbacksString = "";
	GUI* gui;
	//String* retreiveStringOutArg;//the pointer to the string to which we store the reply when requesting the textual value of the element
	std::function<void(String)> retreiveTextCallback;
};
