
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
