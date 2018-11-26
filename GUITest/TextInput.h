#pragma once
#include "GUIElement.h"
#include <functional>

class TextInput: public GUIElement
{
public:
	TextInput(String _id, String _text);

	
	String retrieveText(int clientNo) override;

	//int handleEvent(JsonObject &obj) override;
	
	//String getHTML() override;
	void sendHtml(ESPWebServer& server) override;
private:
	std::function<void()> clickCB = NULL;
};
