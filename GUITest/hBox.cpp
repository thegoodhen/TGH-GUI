// 
// 
// 

#include "hBox.h"



hBox::hBox(String _id)
{
	id = _id;
}
void hBox::openContainer(ESPWebServer& server)
{
	server.sendContent("<div class=\"hBox\">\n");
}
