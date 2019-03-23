#pragma once
#include "GUIElement.h"
#include <functional>

class Checkbox: public GUIElement
{
public:
	Checkbox(String _id, String _text, std::function<void(int, boolean)>clickCallback=NULL);
	

	int handleEvent(int clientNum, JsonObject &obj) override;

	String getHTML() override;

	void sendHtml(ESPWebServer & server) override;

	void onClick(std::function<void(int, boolean)> f);
	void sendInitialization(int clientNo) override;
	int retrieveIntValue(int clientNo) override;
	//String getCSS() override;
	
	//String getHTML() override;
private:
	std::function<void(int, boolean)> onClickCB = NULL;
	int lastRetrievedIntValue = false;
};
