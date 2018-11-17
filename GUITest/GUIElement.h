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
	virtual int handleEvent(int clientNum, JsonObject& obj);
	int handleResponse(JsonObject & obj);
	virtual String getHTML();
	String getId();
	int setText(String theText);
	String getText();
	int retrieveIntValue();
	virtual	String retrieveText();
	void retrieveProperty(std::function<void(String)> func, String propertyName);
	String retrieveProperty(String propertyName);
	String retrieveProperty(String propertyName, int timeout);
	//void retreiveText(String * theText);
	String id;
	void setLineBreak(boolean theBreak);
protected:
	String text;
	String elementType = "div";
	String callbacksString = "";
	GUI* gui;
	//String* retreiveStringOutArg;//the pointer to the string to which we store the reply when requesting the textual value of the element
	std::function<void(String)> retreiveTextCallback;
	std::function<void(String)> retreivePropertyCallback;
	boolean responseFlag=false;
	void storePropertyResponse(String s);
	//a flag which gets set to true when the reply arrives
	void clearResponseFlag();
	String getCallbackString();
	String propertyResponseString;//the String object for storing the value of the property returned from the client side after calling retrieveProperty
	std::vector<String> callbackStrings;//the vector containing all the javascript callbacks for this element
	void addClientSideCallback(String eventName, String eventCode);
	boolean lineBreak=false;
};
