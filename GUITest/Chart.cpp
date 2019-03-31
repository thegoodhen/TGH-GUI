
#include "Chart.h"
#include <functional>

	Chart::Chart(String _id, String _text, String _label0, String _label1, String _label2, String _label3, String _label4)
	{
		id = _id;
		text = _text;
		elementType = "TextArea";
		labelsCount = 0;

		//don't know of a better way than the following... Matlab would handle this using varargin...
		if (_label0 != "")
		{
			_label0.toCharArray(labels[0], 20);
			labelsCount++;
		}
		if (_label1 != "")
		{
			_label1.toCharArray(labels[1], 20);
			labelsCount++;
		}
		if (_label2 != "")
		{
			_label2.toCharArray(labels[2], 20);
			labelsCount++;
		}
		if (_label3 != "")
		{
			_label3.toCharArray(labels[3], 20);
			labelsCount++;
		}
		if (_label4 != "")
		{
			_label4.toCharArray(labels[4], 20);
			labelsCount++;
		}
	}

	String Chart::getLabels()
	{
		String returnString = "[";
		for (int i = 0;i < labelsCount-1;i++)
		{
			returnString += "\""+(String)labels[i] +"\", ";
		}
		returnString += "\"" + (String)labels[labelsCount - 1] + "\"]";
		return returnString;
	}

	String Chart::floatArrayToBracketedList(float* f, int len)
	{
		String returnString = "[";
		for (int i = 0;i < len-1;i++)
		{
			returnString += "\""+(String)f[i] +"\", ";
		}
		returnString += "\"" + (String)f[len- 1] + "\"]";
		return returnString;
	}

	String Chart::floatArrayToTabbedList(float* f, int len)
	{
		String returnString = "";
		for (int i = 0;i < len-1;i++)
		{
			returnString += f[i] + (String)"\t";
		}
		returnString += (String)f[len-1];
		return returnString;
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

	void Chart::setPersistency(boolean _isPersistent)
	{
		if (_isPersistent)
		{
			SPIFFS.begin();
		}
		this->isPersistent = _isPersistent;
	}

	void Chart::savePointsToSpiffs(float* pts, int n)
	{
		String nextLine = this->floatArrayToTabbedList(pts, n);
	    File file = SPIFFS.open(getFilename(), "a");    
		file.println(nextLine);
		file.close();
	}

/**
Sends commands needed to initialize the given element to the client over websockets
**/
void Chart::sendInitialization(int clientNo)
{
	String theInit = "initChart(\""+this->getId()+"\", "+this->getLabels()+");";
	Serial.println("theInit");
	Serial.println(theInit);
	evalAndTell(clientNo, theInit);
	String theLoad = "loadChart(\"" + this->getId() + "\")";
	evalAndTell(clientNo, theLoad);
	//getGUI()->sendText(clientNo, "initialized"+(String)this->getId());
}

void Chart::addPoint(int clientNo, float* arr, int n)
{
	String command = (String)"plot2(\""+this->getId()+"\", "+this->floatArrayToBracketedList(arr,n)+", true);";
	Serial.println(command);
	if (isPersistent)
	{
		this->savePointsToSpiffs(arr, n);
	}
	evalAndToss(clientNo, command);
}

String Chart::getFilename()
{
	return "/" + this->getId() + "_data.txt";
}

void Chart::clear()
{
	evalAndTell(-1, "clearChart(\""+this->getId()+"\")");
	if (isPersistent)
	{
		//delete the file
		SPIFFS.remove(getFilename());
		File f=SPIFFS.open(getFilename(),"w");
		f.close();
	}
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
