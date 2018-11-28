// 
// 
// 

#include "Container.h"

void Container::openContainer(ESPWebServer& server)
{
	server.sendContent("<div class=\"vBox\">\n");
}

void Container::closeContainer(ESPWebServer& server)
{
	server.sendContent("</div>\n");
}

void Container::sendHtml(ESPWebServer& server)
{
	openContainer(server);
	sendContainerItemsHtml(server);
	closeContainer(server);
}

void Container::sendContainerItemsHtml(ESPWebServer& server)
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
	/*
	GUIElement* Container::find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i]->getId() == s)
			{
				return elements[i];
			}
		}
		return NULL;
	}*/


//TODO: this function might be refactored, because currently the code is duplicated between here and GUI...
	GUIElement* Container::find(String s)
	{
		for (std::vector<int>::size_type i = 0; i != elements.size(); i++) {
			if (elements[i]->getElementType() == "CONTAINER")
			{
				GUIElement* foundElement = ((Container*)elements[i])->find(s);
				if (foundElement!=NULL)//if the container found it
				{
					return foundElement;
				}
			}
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
