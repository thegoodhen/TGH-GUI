// 
// 
// 

#include "hBox.h"



hBox::hBox(String _id)
{
	id = _id;
}
void hBox::openContainer(ESP8266WebServer& server)
{
	server.sendContent("<div class=\"hBox\">\n");
}
