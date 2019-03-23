
#include "Chart.h"
#include <functional>

	Chart::Chart(String _id, String _text)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
	}


	void Chart::sendHtml(ESPWebServer& server)
	{
		this->startElementContainer(server);

		server.sendContent("<div ");
		server.sendContent("id=\"");
		server.sendContent(this->id);
		server.sendContent("\" ");
		server.sendContent(this->getCallbackString());
		server.sendContent(" class=\"ct-chart ct-perfect-fourth\">\n");
		server.sendContent("</div>");

		this->endElementContainer(server);
	}


/**
Sends commands needed to initialize the given element to the client over websockets
**/
void Chart::sendInitialization(int clientNo)
{
	String theInit = "initChart(\""+this->getId()+"\");";
	evalAndTell(clientNo, theInit);
	//getGUI()->sendText(clientNo, "initialized"+(String)this->getId());
}

void Chart::addPoint(int clientNo, int lineNo, double x, double y)
{
	String command = (String)"plot(\""+this->getId()+"\", "+lineNo+", ["+x+", "+y+"])";
	evalAndToss(clientNo, command);
}

	/*
	void Chart::sendItemsHtml(ESPWebServer& server)
	{
		for (std::vector<ListItem*>::size_type i = 0; i != theList.size(); i++) {
			{
				//Serial.println(i);
				theList[i]->sendHtml(server);
			}
		}

	}


	void Chart::addItem(ListItem* li)//TODO: add api for removing items
	{
		theList.push_back(li);
	}


	void Chart::onChange(std::function<void(int, ListItem)> f)
	{

		String CBString = "sendJSON({type:\"event\", id: this.id, evType:\"onchange\", index: this.selectedIndex, value: this.options[this.selectedIndex].value, text: this.options[this.selectedIndex].text})";
		this->onChangeCB = f;
		this->addClientSideCallback("onchange", CBString);
	}
	*/

	int Chart::handleEvent(int clientNum, JsonObject &obj) 
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


String Chart::retrieveText(int clientNo)
{
	return this->evalAndTell(clientNo, "var theLb=document.getElementById(\"" + id + "\"); theLb.options[theLb.selectedIndex].value");
}

int Chart::retrieveIntValue(int clientNo)
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
