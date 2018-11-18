
#include "Checkbox.h"
#include <functional>

	Checkbox::Checkbox(String _id, String _text, std::function<void(int, boolean)> clickCallback)
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

	int Checkbox::handleEvent(int clientNum, JsonObject &obj) 
	{
		if (strcmp(obj["evType"], "onClick") == 0)
		{

			if (onClickCB != NULL)
			{
				if (isSynced)
				{
					String v = obj["value"];
					Serial.println("checked:");
					Serial.println(v);
					this->setPropertyOfAllBut(clientNum, "checked", v);//synchronize the switch between clients
				}
				boolean checked = (strcmp(obj["value"], "true") == 0);
				onClickCB(clientNum, checked);
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


	void Checkbox::onClick(std::function<void(int, boolean)> f)
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

	//w3c stuff down there, I kinda just took it from their tutorials
	String Checkbox::getCSS()
	{
		return R"(
/* The switch - the box around the switchSlider */
.switch {
  position: relative;
  display: inline-block;
  width: 60px;
  height: 34px;
}

/* Hide default HTML checkbox */
.switch input {
  opacity: 0;
  width: 0;
  height: 0;
}

/* The switchSlider */
.switchSlider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}

.switchSlider:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}

input:checked + .switchSlider {
  background-color: #2196F3;
}

input:focus + .switchSlider {
  box-shadow: 0 0 1px #2196F3;
}

input:checked + .switchSlider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}

/* Rounded switchSliders */
.switchSlider.round {
  border-radius: 34px;
}

.switchSlider.round:before {
  border-radius: 50%;
}

)";
	}