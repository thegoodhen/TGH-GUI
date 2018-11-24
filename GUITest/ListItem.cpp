
#include "ListItem.h"
#include <functional>

ListItem::ListItem(String _text, String _value, int _id)
	{
		if (_value == "")
		{
			_value = _text;
		}
		text = _text;
		value = _value;
		id = _id;
	}

	/*
	String Label::getHTML() 
	{
		return "<p id=\"" + id + "\" '>" + text + "</p>\n";
	}
	*/


	void ListItem::sendHtml(ESP8266WebServer& server)
	{
		server.sendContent("    <option ");
		server.sendContent("value=\"");
		server.sendContent(this->value);
		server.sendContent("\" ");
		server.sendContent(">");
		server.sendContent(this->text);
		server.sendContent("</option>\n");
	}

	int ListItem::getId()
	{
		return id;
	}

	String ListItem::getText()
	{
		return this->text;
	}

	String ListItem::getValue()
	{
		return this->value;
	}
