
#include "Text.h"
#include <functional>

	Text::Text(String _id, String _text, boolean _oneLine)
	{
		id = _id;
		_text.replace("\n", "<br>\n");
		text = _text;
		elementType = "span";
		oneLine = _oneLine;
	}

	/*
	String Label::getHTML() 
	{
		return "<p id=\"" + id + "\" '>" + text + "</p>\n";
	}
	*/


	void Text::sendHtml(ESPWebServer& server)
	{

		if(oneLine)
		{
			server.sendContent("<span class=normalText ");
		}
		else
		{
			server.sendContent("<div class=normalText ");
		}
		server.sendContent("id=\"");
		server.sendContent(this->id);
		server.sendContent("\" ");
		server.sendContent(this->getCallbackString());
		server.sendContent(">\n");
		server.sendContent(this->text);


		if(oneLine)
		{
			server.sendContent("</span>\n");
		}
		else
		{
			server.sendContent("</div>\n");
		}
	}

