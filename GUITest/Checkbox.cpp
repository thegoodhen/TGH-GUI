
#include "Checkbox.h"
#include <functional>

	Checkbox::Checkbox(String _id, String _text, std::function<void(boolean)> clickCallback)
	{

		id = _id;
		text = _text;
		onClickCB = clickCallback;
		elementType = "checkbox";

		if(clickCallback!=NULL)
		{
		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onClick\", value: this.checked})";
		addClientSideCallback("onclick", CBString);
		}
		//callbacksString = "onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})';";
	}

	int Checkbox::handleEvent(JsonObject &obj) 
	{
		if (strcmp(obj["evType"], "onClick") == 0)
		{
			if (onClickCB != NULL)
			{
				boolean checked = (strcmp(obj["value"], "true") == 0);
				onClickCB(checked);
				return 0;
			}
		}
		return 1;
	}


	String Checkbox::getHTML() 
	{
		char tempStr[400];//But of course, what if the id is too long? Well, then we are f***ed!
		const char* lineBreakStr = this->lineBreak ? "<br>" : "";
		sprintf(tempStr, "%s<input type=\"checkbox\", id=\"%s\", %s>%s",this->text.c_str(), id.c_str(), this->getCallbackString().c_str(),lineBreakStr);
		return tempStr;
	}


	void Checkbox::onClick(std::function<void(boolean)> f)
	{

		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onClick\", value: this.checked})";
		this->onClickCB = f;
		this->addClientSideCallback("onclick", CBString);
	}

	/*
	String Button::getHTML() 
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
*/
