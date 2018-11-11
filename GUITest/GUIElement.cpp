// 
// 
// 

#include "GUIElement.h"


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
