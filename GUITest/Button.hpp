#pragma once
#include "GUIElement.hpp"
#include <functional>

class Button : public GUIElement
{
public:
	Button(String _id, String _text, std::function<void()>clickCallback)
	{
		id = _id;
		text = _text;
		clickCB = clickCallback;
	}

	int handleEvent(JsonObject &obj) override
	{
		if (strcmp(obj["evType"], "click") == 0)
		{
			if (clickCB != NULL)
			{
				clickCB();
				return 0;
			}
		}
		return 1;
	}
	String getHTML()
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
private:
	std::function<void()> clickCB = NULL;
};
