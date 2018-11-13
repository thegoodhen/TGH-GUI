#pragma once
#include "GUIElement.h"
#include <functional>

class Checkbox: public GUIElement
{
public:
	Checkbox(String _id, String _text, std::function<void(boolean)>clickCallback=NULL);
	

	int handleEvent(JsonObject &obj) override;

	String getHTML() override;

	void onClick(std::function<void(boolean)> f);
	
	//String getHTML() override;
private:
	std::function<void(boolean)> onClickCB = NULL;
};
