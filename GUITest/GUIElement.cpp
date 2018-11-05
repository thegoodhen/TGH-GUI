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
	String GUIElement::getHTML()
	{
		return "guiElement";
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
