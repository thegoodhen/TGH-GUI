// 
// 
// 

#include "TabbedPane.h"

TabbedPane::TabbedPane(String _id, String _text)
{
	this->id = _id;
	if (text == "")
	{
		_text = _id;
	}
	else
	{
		this->text = _text;
	}
}

void TabbedPane::addTab(Tab* t)
{
	this->theTabs.push_back(t);
	t->setContainer(this);
	t->setGUI(this->getGUI());
}

void TabbedPane::add(Tab* t)
{
	addTab(t);
}


void TabbedPane::sendHtml(ESP8266WebServer& server)
{
	server.sendContent("<div class=\"tabHeader\">\n");//open the header

	for (std::vector<Tab*>::size_type i = 0; i != theTabs.size(); i++) {
		{
			//Serial.println(i);
			Tab* t = theTabs[i];
			t->sendHeaderHtml(server);	
		}
	}

	server.sendContent("</div>\n");//close the header
	

	//the loop actually has to be iterated twice, this isn't a pointles code duplication...
	for (std::vector<Tab*>::size_type i = 0; i != theTabs.size(); i++) {
		{
			//Serial.println(i);
			Tab* t = theTabs[i];
			t->sendHtml(server);	
		}
	}
	

}

