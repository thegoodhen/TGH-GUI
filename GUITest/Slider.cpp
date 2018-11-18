
#include "Slider.h"
#include <functional>

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

	int Slider::handleEvent(int clientNum, JsonObject &obj) 
	{

		if (strcmp(obj["evType"], "onMouseUp") == 0)//TODO: make this work with touch devices
		{
			if (onClickCB != NULL)
			{

				if (isSynced)
				{
					String v = obj["value"];
					//Serial.println("checked:");
					//Serial.println(v);
					this->setPropertyOfAllBut(clientNum, "value", v);//synchronize the slider between clients
				}
				int val = obj["value"];	
				onClickCB(clientNum, val);
				return 0;
			}
		}
		if (strcmp(obj["evType"], "onInput") == 0)
		{
			if (onInputCB != NULL)
			{

				if (isSynced)
				{
					String v = obj["value"];
					//Serial.println("checked:");
					//Serial.println(v);
					this->setPropertyOfAllBut(clientNum, "value", v);//synchronize the slider between clients
				}
				int val = obj["value"];	
				onInputCB(clientNum, val);
				return 0;
			}
		}
		return 1;
	}
	
	String Slider::getHTML() 
	{
		char tempStr[400];//But of course, what if the id is too long? Well, then we are f***ed!
		const char* lineBreakStr = this->lineBreak ? "<br>\n" : "\n";
		String containerString = "<div class=\"elementContainer\"";
		String labelString = "<label id=\""+this->id+"_lbl"+(String)"\" for=\"" + (String)this->id + "\" class=elementLabel>" + this->text + "</label>";
		sprintf(tempStr, "<input type=\"range\" class=\"slider\" min=\"%d\" max=\"%d\" value=\"%d\" class=\"slider\" id=\"%s\" %s>%s", theMin, theMax, theVal, id.c_str(), this->getCallbackString().c_str(), lineBreakStr);
		String containerStringEnd = "</div>";
		return containerString+labelString+(String)tempStr+containerStringEnd;
	}

	void Slider::onInput(std::function<void(int, int)> f)
	{

		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onInput\", value: this.value})";
		this->onInputCB = f;
		this->addClientSideCallback("oninput", CBString);
	}

	void Slider::onClick(std::function<void(int, int)> f)
	{

		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onMouseUp\", value: this.value})";
		this->onClickCB = f;
		this->addClientSideCallback("onmouseup", CBString);
	}

