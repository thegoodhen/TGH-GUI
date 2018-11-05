

#pragma once
#include "GUIElement.hpp"
#include <vector>

class GUI
{
public:
	GUI()
	{

	}
	/**
	Send the text out using Websockets
	*/
	int sendText(String theText)
	{

		return 1;
	}
	String getHTML()
	{
		String returnString;
		returnString += getHeader();
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			{
				returnString+=elements[i].getHTML();
			}
		}
		returnString += getFooter();
	}
	String getHeader()
	{
		return "<!DOCTYPE html>\n\
<html>\n\
\n";
	}
	String getFooter()
	{
		return "</html> \n";
	}

	String getScript()
	{
		return " <head>\n\
<script>\n\
var theSocket = new WebSocket(\"ws://192.168.0.102:81\", [\'arduino\']);\n\
\n\
function sendJSON(theJSON)\n\
{\n\
  theSocket.send(JSON.stringify(theJSON));\n\
}\n\
\n\
theSocket.onmessage = function (event) {\n\
  console.log(event.data);\n\
}\n\
</script>\n\
</head>";
	}

	void add(GUIElement ge)
	{
		elements.push_back(ge);
		ge.setGUI(this);
	}
	GUIElement* find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i].getId() == s)
			{
				return &elements[i];
			}
		}
		return NULL;
	}

	int handleRequest(JsonObject obj)
	{
		if (strcmp(obj["type"], "event"))
		{
			String id = obj["evType"];
			GUIElement* ge = find(id);
			if (ge != NULL)
			{
				return ge->handleEvent(obj);
			}
			else
			{
				return 1;
			}
		}
		return 0;
	}

private:
	std::vector<GUIElement> elements;
};
