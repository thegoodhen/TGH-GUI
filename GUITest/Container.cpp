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
	std::vector<GUIElement*>* elements = this->gui->getElements();
	for (std::vector<int>::size_type i = 0; i != elements->size(); i++) {
		{
			GUIElement* ge = (*elements)[i];
			if (ge->getContainer() == this)
			{
				ge->sendHtml(server);
			}
		}
	}
}

void Container::add(GUIElement* ge)
{
	ge->setContainer(this);
	this->gui->add(ge);
}

String Container::getElementType()
{
	return "CONTAINER";
}
