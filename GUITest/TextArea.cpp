
#include "TextArea.h"
#include <functional>

	TextArea::TextArea(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
	}

	/*
	String Button::getHTML() 
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
	*/
