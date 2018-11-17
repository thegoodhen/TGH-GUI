#pragma once
#include "GUIElement.h"
#include <functional>

class Slider : public GUIElement
{
public:
	//Slider(String _id, String _text);

	Slider(String _id, String _text, int _min=0, int _max=1023);
	

	int handleEvent(int clientNum, JsonObject &obj) override;
	
	String getHTML() override;
	void onInput(std::function<void(int, int)> f);
	void onClick(std::function<void(int, int)> f);
private:
	std::function<void(int, int)> onClickCB = NULL;
	std::function<void(int, int)> onInputCB = NULL;
	int theMin = 0;
	int theMax = 1023;
	int theVal = 512;

};

