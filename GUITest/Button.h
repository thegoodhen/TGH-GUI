#pragma once
#include "GUIElement.h"
#include <functional>

class Button : public GUIElement
{
public:
	Button(String _id, String _text, std::function<void()>clickCallback);
	

	int handleEvent(JsonObject &obj) override;
	
	String getHTML() override;
private:
	std::function<void()> clickCB = NULL;
};
