// vBox.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "WebServerIncludes.h"
#include "Container.h"

class WiFiManager:public Container
{
public:
	WiFiManager(String _id);
	void connect_CB(int userNo);
	void openContainer(ESPWebServer& server) override;
private:
	void refreshWiFiList_CB(int userNo);
	void onWiFiScanComplete(int networksCount);
	String getStatusString();
};
