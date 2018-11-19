// 
// 
// 

#include "vBox.h"



vBox::vBox(String _id)
{
	id = _id;
}
void vBox::openContainer(ESP8266WebServer& server)
{
	server.sendContent("<div class=\"vBox\">\n");
}
