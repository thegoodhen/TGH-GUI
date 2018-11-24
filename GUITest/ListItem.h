#pragma once
#include <functional>
#include <ESP8266WebServer.h>

class  ListItem
{
public:
	//String getHTML() override;
	ListItem(String _text, String _value="", int id=-1);
	void sendHtml(ESP8266WebServer& server);
	int getId();
	String getText();
	String getValue();
private:
	String value;
	String text;
	int id;
	//std::function<void()> clickCB = NULL;
};
