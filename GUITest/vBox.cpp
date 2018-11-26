// 
// 
// 

#include "vBox.h"



vBox::vBox(String _id)
{
	id = _id;
}
void vBox::openContainer(ESPWebServer& server)
{
	server.sendContent("<div class=\"vBox\">\n");
}
