// 
// 
// 

#include "GUIElement.h"
#include "GUI.h"

#include <Arduino.h>
#ifdef ESP8266
#include "Schedule.h"
#endif

using namespace std::placeholders;  // For _1 in the bind call

//#pragma once
#include "Container.h"


/**
Sends commands needed to initialize the given element to the client over websockets
**/
void GUIElement::sendInitialization(int clientNo)
{
	USE_SERIAL.println(this->getId());
	//getGUI()->sendText(clientNo, "initialized"+(String)this->getId());
}

void GUIElement::setDefaultText(String text)
{
	this->defaultText = text;
}

void GUIElement::setDefaultIntValue(int _intVal)
{
	Serial.println("Ajta krajta, ona se pustila blba funkce! :V");
	this->defaultIntValue = _intVal;
}

void GUIElement::setGUI(GUI* _gui)
{
	gui = _gui;
}

GUI* GUIElement::getGUI()
{
	if (gui != NULL)
	{
		return gui;
	}
	else
	{
		if (enclosingContainer != NULL)
		{
			return this->enclosingContainer->getGUI();
		}
	}
	return NULL;
}

int GUIElement::handleEvent(int clientNum, JsonObject& obj)
{
	return 1;
}
int GUIElement::handleResponse(JsonObject& obj)
{
	tghDbg("response");
	tghDbg((String)millis());
	if (strcmp(obj["subType"], "getText") == 0)
	{
		String str = (obj["text"]);
		tghDbg("handle Response");
		//*retreiveStringOutArg = str;
		retreiveTextCallback(str);
	}

	if (strcmp(obj["subType"], "getProperty") == 0||strcmp(obj["subType"], "evalAndTell")==0)
	{
		String str = (obj["value"]);
		tghDbg("got some getProperty response");
		//*retreiveStringOutArg = str;
		responseCallback(str);
	}
	return 0;
}


/*
@Deprecated
*/
String GUIElement::getHTML()
{
	const char* lineBreakStr = this->lineBreak ? "<br>\n" : "\n";
	return "<" + this->elementType + " id=\"" + id + "\" " + this->getCallbackString() + ">" + text + "</" + elementType + ">"+lineBreakStr;
}


void GUIElement::sendHtml(ESPWebServer& server)
{
	server.sendContent(getHTML());//this is just for now, getHtml is obsolete
}

String GUIElement::getId()
{
	return id;
}

/*
int GUIElement::setText(int clientNo, String theText)
{
	DynamicJsonBuffer jb(theText.length() + 100);
	JsonObject& obj = jb.createObject();
	obj["type"] = "setText";
	obj["id"] = id;
	obj["newText"] = theText;
	String sentString;
	obj.printTo(sentString);
	gui->sendText(clientNo, sentString);
	return 0;
}
*/


/**
Broadcasts the request to set some text to all the connected clients
**/
int GUIElement::setText(int clientNum, String theText)
{
	/*
	DynamicJsonBuffer  jb(theText.length() + 100);
	JsonObject& obj = jb.createObject();
	obj["type"] = "setText";
	obj["id"] = id;
	obj["newText"] = theText;
	String sentString;
	obj.printTo(sentString);
	gui->sendText(ALL_CLIENTS, sentString);
	return 0;
	*/
	return setProperty(clientNum, "innerHTML", theText);
}

int GUIElement::setProperty(int clientNum, String propertyName, String propertyValue)
{
	DynamicJsonBuffer jb(propertyName.length()+propertyValue.length()+200);
	JsonObject& obj = jb.createObject();
	obj["type"] = "setProperty";
	obj["id"] = id;
	obj["propertyName"] = propertyName;
	obj["value"] = propertyValue;
	String sentString;
	obj.printTo(sentString);
	gui->sendText(clientNum, sentString);
	return 0;
}

//TODO: Think about how we can refactor this 
int GUIElement::setPropertyOfAllBut(int clientNo, String propertyName, String propertyValue)
{
	DynamicJsonBuffer jb(propertyName.length()+propertyValue.length()+200);
	JsonObject& obj = jb.createObject();
	obj["type"] = "setProperty";
	obj["id"] = id;
	obj["propertyName"] = propertyName;
	obj["value"] = propertyValue;
	String sentString;
	obj.printTo(sentString);
	gui->sendTextToAllBut(clientNo, sentString);
	return 0;

}


String GUIElement::getText()
{
	return this->text;
}



int GUIElement::retrieveIntValue(int clientNo)
{
	String s = this->retrieveProperty(clientNo, "value");
	const char* str = s.c_str();
	char* ptr;
	return strtol(str, &ptr, 10);//yea, but handle some error checking as well please
}


/*
A non-blocking function, which allows the user to request that a the String supplied by them will sometime
in the future be filled up with the text of the (remote) user interface element. In case of text boxes,
this text should be the content of the textbox, in case of listboxes, it should be the currently selected item, etc.
*/
String GUIElement::retrieveText(int clientNo)
{
	return this->retrieveProperty(clientNo, "InnerHtml");
}

/*
A non-blocking function, which allows the user to request that a the String supplied by them will sometime
in the future be filled up with a textual representation of some property of the (remote) user interface element.
*/
int GUIElement::retrieveProperty(int clientNumber, std::function<void(String)> func, String propertyName)//TODO: handle multiple requests at the same time!
{
	tghDbg("retProperty");
	tghDbg((String)millis());
	//retreiveStringOutArg = theText;//set the pointer
	responseCallback = func;
	StaticJsonBuffer<500> jb;
	JsonObject& obj = jb.createObject();
	obj["type"] = "getProperty";
	obj["id"] = id;
	obj["propertyName"] = propertyName;
	String str;
	obj.printTo(str);
	return this->gui->sendText(clientNumber, str);
}

/*
Blocking function, which requests a property to be retrieved and then waits for the reply; returns empty string on timeout
*/
String GUIElement::retrieveProperty(int clientNumber, String propertyName)//TODO: exit if client not connected
{
	return GUIElement::retrieveProperty(clientNumber, propertyName, 250);
}

String GUIElement::retrieveProperty(int clientNumber, String propertyName, int timeout)
{
	clearResponseFlag();
	auto f1 = std::bind(&GUIElement::storePropertyResponse, this, _1);
	if (retrieveProperty(clientNumber, f1, propertyName) != 0)//something went wrong!
	{
		return "ERROR_RETRIEVING_PROPERTY";
	}
	return waitForResponse(timeout);
}

String GUIElement::waitForResponse(int timeout)
{
	tghDbg("waiting for property response");
	unsigned long startMillis = millis();
	while (millis() < (startMillis + timeout))
	{
		this->getGUI()->loop();
		//the following line was commented out
		//run_scheduled_functions();
		yield();
		//ets_post(1, 0, 0);
		//esp_schedule();
		if (this->responseFlag == true)
		{
			return this->propertyResponseString;
		}
	}
	return "";
}

int GUIElement::evalAndToss(int clientNo, String whatToEval)
{

	StaticJsonBuffer<500> jb;
	JsonObject& obj = jb.createObject();
	obj["type"] = "evalAndToss";
	obj["id"] = id;
	obj["value"] = whatToEval;
	String str;
	obj.printTo(str);
	return this->getGUI()->sendText(clientNo, str);
}

/*
A non-blocking function, which allows the user to request that a the String supplied by them will sometime
in the future be filled up with a textual representation of a return value of whatever happense when the "whatToEval" string gets passed to the JavaScript eval
*/
int GUIElement::evalAndTell(int clientNumber, std::function<void(String)> func, String whatToEval)//TODO: handle multiple requests at the same time!
{
	tghDbg("evalAndTell");
	tghDbg((String)millis());
	//retreiveStringOutArg = theText;//set the pointer
	responseCallback = func;
	StaticJsonBuffer<500> jb;
	JsonObject& obj = jb.createObject();
	obj["type"] = "evalAndTell";
	obj["id"] = id;
	obj["value"] = whatToEval;
	String str;
	obj.printTo(str);
	return this->getGUI()->sendText(clientNumber, str);
}



String GUIElement::evalAndTell(int clientNumber, String whatToEval)
{
	return evalAndTell(clientNumber, whatToEval, 250);
}

/*
Blocking function, which requests the call of js eval() on the string provided and then blocks until it gets the response; returns empty string on timeout
*/
String GUIElement::evalAndTell(int clientNumber, String whatToEval, int timeout)
{
	clearResponseFlag();
	auto f1 = std::bind(&GUIElement::storePropertyResponse, this, _1);
	if (evalAndTell(clientNumber, f1, whatToEval) != 0)//something went wrong!
	{
		return "ERROR_WAITING_FOR_EVAL";
	}
	return waitForResponse(timeout);
}

void GUIElement::setLineBreak(boolean theBreak)
{
	this->lineBreak = theBreak;
}

/*
Stores the response to "retrieveProperty" into the propertyResponseString field
*/
void GUIElement::storePropertyResponse(String s)
{
	tghDbg("storing property response");
	tghDbg(s);
	this->propertyResponseString = s;
	this->responseFlag = true;
}
void GUIElement::clearResponseFlag()
{
	this->responseFlag = false;
}

void GUIElement::addClientSideCallback(String eventName, String eventCode)
{
	for (std::vector<String>::size_type i = 0; i != callbackStrings.size(); i++) {
		if (callbackStrings[i].startsWith(eventName))//if we already have this callback
		{
			callbackStrings[i] = eventName + "='" + eventCode + "'";
			return;
		}
	}
	callbackStrings.push_back(eventName + "='" + eventCode + "'");
}

String GUIElement::getCallbackString()
{
	String returnString = " ";
	//returnString+
	for (std::vector<String>::size_type i = 0; i != callbackStrings.size(); i++) {
		{
			returnString += callbackStrings[i] + " ";
		}
	}
	return returnString;
}

void GUIElement::setSynced(boolean _synced)
{
	this->isSynced = _synced;
}

//TODO: this is not related to vBoxes and hBoxes at all, it's just the wrapper containing the label of this element and the element itself, it should be renamed!
void GUIElement::startElementContainer(ESPWebServer& server)
{
	server.sendContent("<div class=\"elementContainer\">\n");
	char labelStr[400];
	String lblName = this->id + "_lbl";
	sprintf(labelStr, "<label id=\"%s\"for=\"%s\" class=\"elementLabel\">%s</label>\n", lblName.c_str(), this->id.c_str(), this->text.c_str());
	server.sendContent(labelStr);
}

//TODO: this is not related to vBoxes and hBoxes at all, it's just the wrapper containing the label of this element and the element itself, it should be renamed!
void GUIElement::endElementContainer(ESPWebServer& server)
{
	server.sendContent("</div>\n");
}

void GUIElement::setContainer(Container* c)
{
	this->enclosingContainer = c;
}

Container* GUIElement::getContainer()
{
	return this->enclosingContainer;
}

String GUIElement::getElementType()
{
	return "NORMAL";
}