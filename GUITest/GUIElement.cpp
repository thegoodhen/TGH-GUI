// 
// 
// 

#include "GUIElement.h"

#include <Arduino.h>
#include "Schedule.h"

using namespace std::placeholders;  // For _1 in the bind call

//#pragma once



	void GUIElement::setGUI(GUI* _gui)
	{
		gui = _gui;
	}
	int GUIElement::handleEvent(JsonObject& obj)
	{
		return 1;
	}
	int GUIElement::handleResponse(JsonObject& obj)
	{
		Serial.println("response");
		Serial.println(millis());
		if (strcmp(obj["subType"],"getText")==0)
		{
			String str=(obj["text"]);
			Serial.println("handle Response");
			//*retreiveStringOutArg = str;
			retreiveTextCallback(str);
		}

		if (strcmp(obj["subType"],"getProperty")==0)
		{
			String str=(obj["value"]);
			Serial.println("got some getProperty response");
			//*retreiveStringOutArg = str;
			retreivePropertyCallback(str);
		}
		return 0;
	}


	String GUIElement::getHTML()
	{
		return "<"+this->elementType+" id=\""+id+"\" "+this->callbacksString+">"+text+"</"+elementType+">";
	}
	String GUIElement::getId()
	{
		return id;
	}

	int GUIElement::setText(String theText)
	{
		DynamicJsonBuffer jb(theText.length() + 100);
		JsonObject& obj = jb.createObject();
		obj["type"] = "setText";
		obj["id"] = id;
		obj["newText"] = theText;
		String sentString;
		obj.printTo(sentString);
		gui->sendText(sentString);
		return 0;

	}
	/*
	A non-blocking function, which allows the user to request that a the String supplied by them will sometime
	in the future be filled up with the text of the (remote) user interface element. In case of text boxes,
	this text should be the content of the textbox, in case of listboxes, it should be the currently selected item, etc.
	*/
	void GUIElement::retreiveText(std::function<void(String)> func)
	{
		Serial.println("request");
		Serial.println(millis());
		//retreiveStringOutArg = theText;//set the pointer
		retreiveTextCallback = func;
		StaticJsonBuffer<500> jb;
		JsonObject& obj = jb.createObject();
		obj["type"] = "getText";
		obj["id"] = id;
		String str;
		obj.printTo(str);
		this->gui->sendText(str);
	}

	/*
	A non-blocking function, which allows the user to request that a the String supplied by them will sometime
	in the future be filled up with a textual representation of some property of the (remote) user interface element. 
	*/
	void GUIElement::retrieveProperty(std::function<void(String)> func, String propertyName)//TODO: handle multiple requests at the same time!
	{
		Serial.println("retProperty");
		Serial.println(millis());
		//retreiveStringOutArg = theText;//set the pointer
		retreivePropertyCallback = func;
		StaticJsonBuffer<500> jb;
		JsonObject& obj = jb.createObject();
		obj["type"] = "getProperty";
		obj["id"] = id;
		obj["propertyName"] = propertyName;
		String str;
		obj.printTo(str);
		this->gui->sendText(str);
	}

	/*
	Blocking function, which requests a property to be retrieved and then waits for the reply; returns empty string on timeout
	*/
	String GUIElement::retrieveProperty(String propertyName)
	{
		return GUIElement::retrieveProperty(propertyName, 1000);
	}

	String GUIElement::retrieveProperty(String propertyName, int timeout)
{
		clearResponseFlag();
		auto f1 = std::bind(&GUIElement::storePropertyResponse, this,_1);
		retrieveProperty(f1, propertyName);
		Serial.println("waiting for property response");
		unsigned long startMillis = millis();
		while (millis()<(startMillis+timeout))
		{
			this->gui->loop();
			run_scheduled_functions();
			ets_post(1, 0, 0);
			//esp_schedule();
			if (this->responseFlag == true)
			{
				return this->propertyResponseString;
			}
		}
		return "";
	}

	/*
	Stores the response to "retrieveProperty" into the propertyResponseString field
	*/
	void GUIElement::storePropertyResponse(String s)
	{
		Serial.println("storing property response");
		Serial.println(s);
		this->propertyResponseString = s;
		this->responseFlag = true;
	}
	void GUIElement::clearResponseFlag()
	{
		this->responseFlag = false;
	}

