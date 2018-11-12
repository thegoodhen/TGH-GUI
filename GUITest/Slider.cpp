
#include "Slider.h"
#include <functional>

	Slider::Slider(String _id, String _text)
	{
		Slider(_id, _text, 0, 1023);
	}
	Slider::Slider(String _id, String _text, int _min, int _max)
	{
		id = _id;

		text = _text;
		//clickCB = clickCallback;
		//elementType = "button";
		//callbacksString = "onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})';";
		theMin = _min;
		theMax = _max;
	}

	int Slider::handleEvent(JsonObject &obj) 
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
	
	String Slider::getHTML() 
	{
		char tempStr[200];//But of course, what if the id is too long? Well, then we are f***ed!
		sprintf(tempStr, "<input type=\"range\" min=\"%d\" max=\"%d\" value=\"%d\" class=\"slider\" id=\"%s\" %s>", theMin, theMax, theVal, id.c_str(), this->getCallbackString().c_str());
		return tempStr;
	}

	void Slider::onInput(std::function<void(int)> f)
	{

		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onInput\"})";
		this->onInputCB = f;
		this->addClientSideCallback("oninput", CBString);
	}

