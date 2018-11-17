#pragma once
#include "GUIElement.h"
#include <functional>

class Button : public GUIElement
{
public:
	Button(String _id, String _text, std::function<void(int)>clickCallback);
	

	int handleEvent(int clientNo, JsonObject &obj) override;
	
	//String getHTML() override;
private:
	std::function<void(int)> clickCB = NULL;
};
