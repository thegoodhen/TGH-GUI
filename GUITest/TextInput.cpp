
#include "TextInput.h"
#include <functional>


	TextInput::TextInput(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
		isSynced = true;//TODO: add this as a constructor parameter instead...
	}

	String TextInput::retrieveText(int clientNo) 
	{
		String s=retrieveProperty(clientNo, "value");
		if (isSynced)
		{
			this->lastRetrievedText = s;
		}
		return s;
	}


	void TextInput::sendInitialization(int clientNo)
	{
		this->setProperty(clientNo, "value", this->lastRetrievedText);
		//getGUI()->sendText(clientNo, "initialized"+(String)this->getId());
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
