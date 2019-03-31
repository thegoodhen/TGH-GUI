// GUIElement.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Arduino.h"
#include <ArduinoJson.h>
//#include "Container.h"
#include <functional>
#include "WebServerIncludes.h"
#include "Debugging.h"
class GUI;
class Container;




class GUIElement
{
public:

	virtual void sendInitialization(int clientNo);

	void setDefaultText(String text);

	virtual void setDefaultIntValue(int _intVal);

	void setGUI(GUI* _gui);
	GUI * getGUI();
	virtual int handleEvent(int clientNum, JsonObject& obj);
	int handleResponse(JsonObject & obj);
	virtual String getHTML();
	virtual void sendHtml(ESPWebServer& server);
	String getId();
	int setText(int clientNo, String theText);
	//int setText(String theText);
	String getText();
	virtual int retrieveIntValue(int clientNo);
	//virtual	String retrieveText();
	virtual String retrieveText(int clientNo);
	//void retrieveProperty(std::function<void(String)> func, String propertyName);
	int retrieveProperty(int clientNumber, std::function<void(String)> func, String propertyName);
	//String retrieveProperty(String propertyName);
	String retrieveProperty(int clientNumber, String propertyName);
	String retrieveProperty(int clientNumber, String propertyName, int timeout);
	String waitForResponse(int timeout);
	int evalAndToss(int clientNo, String whatToEval);
	//int setProperty(String propertyName, String propertyValue);
	int setProperty(int clientNumber, String propertyName, String propertyValue);
	int setPropertyOfAllBut(int clientNo, String propertyName, String propertyValue);
	//String retrieveProperty(String propertyName, int timeout);
	//void retreiveText(String * theText);
	String id;
	int evalAndTell(int clientNumber, std::function<void(String)> func, String whatToEval);
	String evalAndTell(int clientNumber, String propertyName);
	String evalAndTell(int clientNumber, String propertyName, int timeout);
	void setLineBreak(boolean theBreak);
	void setSynced(boolean _synced);
	void setContainer(Container* c);
	Container * getContainer();
	virtual String getElementType();
protected:
	String text;
	String defaultText;
	String elementType = "div";
	String callbacksString = "";
	//String* retreiveStringOutArg;//the pointer to the string to which we store the reply when requesting the textual value of the element
	std::function<void(String)> retreiveTextCallback;
	std::function<void(String)> responseCallback;
	boolean responseFlag=false;
	void storePropertyResponse(String s);
	//a flag which gets set to true when the reply arrives
	void clearResponseFlag();
	String getCallbackString();
	String propertyResponseString;//the String object for storing the value of the property returned from the client side after calling retrieveProperty
	std::vector<String> callbackStrings;//the vector containing all the javascript callbacks for this element
	void addClientSideCallback(String eventName, String eventCode);
	boolean lineBreak=false;
	boolean isSynced=false;

	void startElementContainer(ESPWebServer& server);
	void endElementContainer(ESPWebServer& server);
	Container* enclosingContainer=NULL;
	int defaultIntValue=-1;
	int lastRetrievedIntValue = -1;
private:
	GUI* gui=NULL;
};
