
#include "Heading.h"
#include <functional>

	Heading::Heading(String _id, int lvl, String _text)
	{
		id = _id;
		text = _text;
		elementType = (String)"h"+lvl;
	}

	/*
	String Label::getHTML() 
	{
		return "<p id=\"" + id + "\" '>" + text + "</p>\n";
	}
	*/
