// 
// 
// 

#include "WiFiManager.h"
#include "ElementTypes.h"
#include <functional>

using namespace std::placeholders;  // For _1 in the bind call




WiFiManager::WiFiManager(String _id)
{
	id = _id;
	Label* l = new Label(id + "statusLbl", "Status: ");
	l->setDefaultText("disconnected");

	Label* l2 = new Label(id + "ipLbl", "IP: ");
	l2->setDefaultText("disconnected");

	ListBox* lb = new ListBox(id + "lb1", "Networks: ");

	auto f1 = std::bind(&WiFiManager::refreshWiFiList_CB, this,_1);

	Button*b = new Button(id + "_refreshBtn", "Refresh list", f1);

	TextInput* tInput = new TextInput(id + "_pass", "Password: ");
	tInput->setIsPassword(true);

	auto f2 = std::bind(&WiFiManager::connect_CB, this,_1);
	Button* bConnect = new Button(id + "_connectBtn", "Connect", f2);


	this->add(l);
	this->add(l2);
	this->add(lb);
	this->add(b);
	this->add(tInput);
	this->add(bConnect);
}

void WiFiManager::connect_CB(int userNo)
{
	ListBox*lb = (ListBox*)this->find(id + "lb1");
	TextInput* pass = (TextInput*)this->find(id + "_pass");
	String APName=lb->retrieveText(userNo);
	String APPass=pass->retrieveText(userNo);
	//Serial.println(APName);
	//Serial.println(APPass);
	
	Label* l = (Label*)this->find(id + "statusLbl");
	l->setText(userNo,"Connecting...");

	WiFi.disconnect();


	WiFi.begin(APName.c_str(), APPass.c_str());

}

void WiFiManager::refreshWiFiList_CB(int userNo)
{
	Serial.println("WiFi list refresh in progres...");
	auto f1 = std::bind(&WiFiManager::onWiFiScanComplete, this, _1);
	WiFi.scanNetworksAsync(f1);

	Label* l = (Label*)this->find(id + "statusLbl");
	l->setText(userNo,"Scanning...");



}

void WiFiManager::onWiFiScanComplete(int networksCount)
{
	ListBox*lb = (ListBox*)this->find(id + "lb1");
	lb->clearList();
	for (int i = 0;i < networksCount;i++)
	{
		lb->addItem(new ListItem(WiFi.SSID(i).c_str(),WiFi.SSID(i).c_str()));
	}
	lb->updateItemsDisplay(-1);

	Label* l = (Label*)this->find(id + "statusLbl");
	l->setText(-1,getStatusString());

}

String WiFiManager::getStatusString()
{
	return WiFi.isConnected() ? "CONNECTED" : "DISCONNECTED";
}

void WiFiManager::openContainer(ESPWebServer& server)
{
	server.sendContent("<div class=\"vBox\">\n");//this is intentional, the WiFiManager is actually styled just like a vBox...
}
