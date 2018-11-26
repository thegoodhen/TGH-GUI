#pragma once
#include <functional>
#include "WebServerIncludes.h"

class  ListItem
{
public:
	//String getHTML() override;
	ListItem(String _text, String _value="", int id=-1);
	void sendHtml(ESPWebServer& server);
	int getId();
	String getText();
	String getValue();
private:
	String value;
	String text;
	int id;
	//std::function<void()> clickCB = NULL;
};
