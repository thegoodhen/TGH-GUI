
#include "Button.h"
#include <functional>

	Button::Button(String _id, String _text, std::function<void(int)>clickCallback)
	{

		id = _id;
		text = _text;
		clickCB = clickCallback;
		elementType = "button";

		addClientSideCallback("onclick", R"(sendJSON({type:"event", id: this.id, evType:"click"}))");
		//callbacksString = "onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})';";
	}

	int Button::handleEvent(int clientNum, JsonObject &obj) 
	{
		if (strcmp(obj["evType"], "click") == 0)
		{
			if (clickCB != NULL)
			{
				clickCB(clientNum);
				return 0;
			}
		}
		return 1;
	}
	/*
	String Button::getHTML() 
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
*/
