#pragma once
#include "GUIElement.h"
#include <functional>
#include "ListItem.h"
#include <FS.h>   // Include the SPIFFS library

class Chart: public GUIElement
{
public:

	
	String retrieveText(int clientNo) override;

	int retrieveIntValue(int clientNo) override;

	//int handleEvent(JsonObject &obj) override;
	
	Chart(String _id, String _text, boolean _xIsDate, String _label1="x", String _label2="y", String _label3="", String _label4="", String _label5="");


	String getLabels();

	String doubleArrayToBracketedList(double * f, int len);


	String doubleArrayToTabbedList(double * f, int len);


	//String getHTML() override;
	void sendHtml(ESPWebServer& server) override;
	void setPersistency(boolean _isPersistent);
	void savePointsToSpiffs(double * pts, int n);
	void sendItemsHtml(ESPWebServer& server);
	void addItem(ListItem* li);
	void onChange(std::function<void(int, ListItem)> f);
	void sendInitialization(int clientNo) override;
	void addPoint(int clientNo, double* arr, int n);
	String getFilename();
	void clear();
	int handleEvent(int clientNum, JsonObject &obj) override;
private:
	std::function<void(int, ListItem)> onChangeCB = NULL;
	std::vector<ListItem*> theList;
	char labels[5][20];
	int labelsCount = 0;
	boolean isPersistent = false;
	boolean xIsDate = false;
};
