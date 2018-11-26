// SpiffsUtils.h

#pragma once
#include <FS.h>   // Include the SPIFFS library
#include "WebServerIncludes.h"


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

String getContentType(String filename) ; // convert the file extension to the MIME type
bool handleFileRead(ESPWebServer& server, String path) ; // send the right file to the client (if it exists)
