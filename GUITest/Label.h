#pragma once
#include "GUIElement.h"
#include <functional>

class Label : public GUIElement
{
public:
	Label(String _id, String _text);
	//String getHTML() override;
	void sendHtml(ESPWebServer& server) override;
private:
	//std::function<void()> clickCB = NULL;
};
