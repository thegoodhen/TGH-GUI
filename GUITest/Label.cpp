
#include "Label.h"
#include <functional>

	Label::Label(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "span";
	}

	/*
	String Label::getHTML() 
	{
		return "<p id=\"" + id + "\" '>" + text + "</p>\n";
	}
	*/


	void Label::sendHtml(ESP8266WebServer& server)
	{
		this->startElementContainer(server);

		server.sendContent("<span class=display ");
		server.sendContent("id=\"");
		server.sendContent(this->id);
		server.sendContent("\" ");
		server.sendContent(this->getCallbackString());
		server.sendContent(">\n");
		server.sendContent(this->text);
		server.sendContent("</span>\n");

		this->endElementContainer(server);
	}

