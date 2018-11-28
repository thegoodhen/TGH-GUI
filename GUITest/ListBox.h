#pragma once
#include "GUIElement.h"
#include <functional>
#include "ListItem.h"

class ListBox: public GUIElement
{
public:
	 ListBox(String _id, String _text);

	
	String retrieveText(int clientNo) override;

	int retrieveIntValue(int clientNo) override;

	//int handleEvent(JsonObject &obj) override;
	
	//String getHTML() override;
	void sendHtml(ESPWebServer& server) override;
	void sendItemsHtml(ESPWebServer& server);
	void addItem(ListItem* li);
	void onChange(std::function<void(int, ListItem)> f);
	int handleEvent(int clientNum, JsonObject &obj) override;
private:
	std::function<void(int, ListItem)> onChangeCB = NULL;
	std::vector<ListItem*> theList;
};
