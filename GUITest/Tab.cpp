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

void Tab::sendHeaderHtml(ESPWebServer& server)
{
	server.sendContent("<button class=\"tabLink\" onclick='activateTab(event, \""); 
	server.sendContent(this->id); 
	server.sendContent("\", "); 
	server.sendContent("\""); 
	server.sendContent(this->enclosingContainer->getId()); 
	server.sendContent("\")\'>"); 
	server.sendContent(this->text);
	server.sendContent("</button>\n");
}



void Tab::openContainer(ESPWebServer& server)
{
	server.sendContent("<div class=\"tabContent\" id=\"");
	server.sendContent(this->id);
	server.sendContent("\" data-tabbed-pane-id=\"");
	server.sendContent(this->enclosingContainer->getId());
	server.sendContent("\">\n");
}

