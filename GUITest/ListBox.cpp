
#include "ListBox.h"
#include <functional>

	ListBox::ListBox(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
	}


	void ListBox::sendHtml(ESPWebServer& server)
	{
		this->startElementContainer(server);

		server.sendContent("<select ");
		server.sendContent("id=\"");
		server.sendContent(this->id);
		server.sendContent("\" ");
		server.sendContent(this->getCallbackString());
		server.sendContent(">\n");
		sendItemsHtml(server);
		server.sendContent("</select>\n");

		this->endElementContainer(server);
	}

	void ListBox::sendItemsHtml(ESPWebServer& server)
	{
		for (std::vector<ListItem*>::size_type i = 0; i != theList.size(); i++) {
			{
				//Serial.println(i);
				theList[i]->sendHtml(server);
			}
		}

	}


	void ListBox::addItem(ListItem* li)//TODO: add api for removing items
	{
		theList.push_back(li);
	}


	void ListBox::onChange(std::function<void(int, ListItem)> f)
	{

		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onchange\", index: this.selectedIndex, value: this.options[this.selectedIndex].value, text: this.options[this.selectedIndex].text})";
		this->onChangeCB = f;
		this->addClientSideCallback("onchange", CBString);
	}

	int ListBox::handleEvent(int clientNum, JsonObject &obj) 
	{
		if (strcmp(obj["evType"], "onchange") == 0)
		{

			if (onChangeCB!= NULL)
			{
				int index = obj["index"];
				String value = obj["value"];
				String text = obj["text"];
				//Serial.println("teïkonc jsem tady");
				//Serial.println(value);

				ListItem li = ListItem(text, value, index);

				if (isSynced)
				{
					this->setPropertyOfAllBut(clientNum, "selectedIndex", (String)index);//synchronize the switch between clients
				}
				onChangeCB(clientNum, li);
				return 0;
			}
		}
		return 1;
	}


String ListBox::retrieveText(int clientNo)
{
	return this->evalAndTell(clientNo, "var theLb=document.getElementById(\"" + id + "\"); theLb.options[theLb.selectedIndex].value");
}

int ListBox::retrieveIntValue(int clientNo)
{
	String s=this->evalAndTell(clientNo, "var theLb=document.getElementById(\"" + id + "\"); theLb.selectedIndex");
	const char* str = s.c_str();
	char* ptr;
	return strtol(str, &ptr, 10);//yea, but handle some error checking as well please
}

	/*
	String Button::getHTML() 
	{
		return "<button id=\"" + id + "\" onclick='sendJSON({type:\"event\", id: this.id, evType:\"click\"})'>" + text + "</button>\n";
	}
	*/
