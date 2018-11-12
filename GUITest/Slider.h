#pragma once
#include "GUIElement.h"
#include <functional>

class Slider : public GUIElement
{
public:
	Slider(String _id, String _text);

	Slider(String _id, String _text, int _min, int _max);
	

	int handleEvent(JsonObject &obj) override;
	
	String getHTML() override;
private:
	std::function<void()> clickCB = NULL;
	int theMin = 0;
	int theMax = 1023;
	int theVal = 512;
};
