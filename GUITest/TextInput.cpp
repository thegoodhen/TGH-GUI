
#include "TextInput.h"
#include <functional>

	TextInput::TextInput(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
	}

	String TextInput::retrieveText(int clientNo) 
	{
		return this->retrieveProperty(clientNo, "value");
	}

	void TextInput::sendHtml(ESPWebServer& server)
	{
		this->startElementContainer(server);

		server.sendContent("<input type='text' ");
		server.sendContent("id=\"");
		server.sendContent(this->id);
		server.sendContent("\", ");
		server.sendContent(this->getCallbackString());
		server.sendContent(">\n");
		server.sendContent("</input>\n");

		this->endElementContainer(server);
	}



	/*
	String Button::getHTML() 
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
	*/
