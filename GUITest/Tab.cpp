// 
// 
// 

#include "Tab.h"

Tab::Tab(String _id, String _text)
{
	this->id = _id;
	if (_text == "")
	{
		_text = _id;
	}
	this->text = _text;
}

void Tab::sendHeaderHtml(ESP8266WebServer& server)
{
	server.sendContent("<button class=\"tabLink\" onclick='activateTab(event, \""); 
	server.sendContent(this->id); 
	server.sendContent("\")\'>"); 
	server.sendContent(this->text);
	server.sendContent("</button>\n");
}



void Tab::openContainer(ESP8266WebServer& server)
{
	server.sendContent("<div class=\"tabContent\" id=\"");
	server.sendContent(this->id);
	server.sendContent("\">\n");
}

