#pragma once
#include "GUIElement.h"
#include <functional>

class Text: public GUIElement
{
public:
	Text(String _id, String _text, boolean _oneLine=false);
	//String getHTML() override;
	void sendHtml(ESPWebServer& server) override;
private:
	boolean oneLine;
	//std::function<void()> clickCB = NULL;
};
