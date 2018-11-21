
#include "TextArea.h"
#include <functional>

	TextArea::TextArea(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
	}

	String TextArea::retrieveText(int clientNo) 
	{
		return this->retrieveProperty(clientNo, "value");
	}

	void TextArea::sendHtml(ESP8266WebServer& server)
	{
		this->startElementContainer(server);

		server.sendContent("<TextArea ");
		server.sendContent("id=\"");
		server.sendContent(this->id);
		server.sendContent("\", ");
		server.sendContent(this->getCallbackString());
		server.sendContent(">\n");
		server.sendContent("</TextArea>\n");

		this->endElementContainer(server);
	}



	/*
	String Button::getHTML() 
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
	*/
