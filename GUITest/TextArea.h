#pragma once
#include "GUIElement.h"
#include <functional>

class TextArea: public GUIElement
{
public:
	TextArea(String _id, String _text);

	
	String retrieveText(int clientNo) override;

	//int handleEvent(JsonObject &obj) override;
	
	//String getHTML() override;
private:
	std::function<void()> clickCB = NULL;
};
