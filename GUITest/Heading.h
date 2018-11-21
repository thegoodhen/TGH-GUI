#pragma once
#include "GUIElement.h"
#include <functional>

class Heading : public GUIElement
{
public:
	Heading(String _id, int lvl, String _text);
	//String getHTML() override;
private:
	//std::function<void()> clickCB = NULL;
};
