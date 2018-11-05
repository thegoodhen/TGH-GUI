

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

	void add(GUIElement ge)
	{
		elements.push_back(ge);
		ge.setGUI(this);
	}
	GUIElement* find(String s)
	{
			for(std::vector<int>::size_type i = 0; i != elements.size(); i++) {
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
