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
	server.sendContent("</div>");
}
void Container::sendHtml(ESP8266WebServer& server)
{
	openContainer(server);
	std::vector<GUIElement*>* elements = this->gui->getElements();
	for (std::vector<int>::size_type i = 0; i != elements->size(); i++) {
		{
			//Serial.println(i);
			GUIElement* ge = (*elements)[i];
			if (ge->getContainer() == this)
			{
				ge->sendHtml(server);
			}
		}
	}
	closeContainer(server);
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
