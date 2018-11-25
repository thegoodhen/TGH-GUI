// 
// 
// 

#include "Container.h"

void Container::openContainer(ESP8266WebServer& server)
{
	server.sendContent("<div class=\"vBox\">\n");
}

void Container::closeContainer(ESP8266WebServer& server)
{
	server.sendContent("</div>\n");
}

void Container::sendHtml(ESP8266WebServer& server)
{
	openContainer(server);
	sendContainerItemsHtml(server);
	closeContainer(server);
}

void Container::sendContainerItemsHtml(ESP8266WebServer& server)
{
	for (std::vector<GUIElement*>::size_type i = 0; i != elements.size(); i++) {
		GUIElement* ge = (elements)[i];
		ge->sendHtml(server);
	}

}


//TODO: this function might be refactored, because currently the code is duplicated between here and GUI...
	void Container::add(GUIElement* ge)
	{
		if (this->find(ge->getId()))//if already there, fail; TODO: change the return type to int to signal errors
		{
			return;
		}
		ge->setContainer(this);
		elements.push_back(ge);
	}

//TODO: this function might be refactored, because currently the code is duplicated between here and GUI...
	GUIElement* Container::find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i]->getId() == s)
			{
				return elements[i];
			}
		}
		return NULL;
	}


String Container::getElementType()
{
	return "CONTAINER";
}
