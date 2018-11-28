#pragma once

#ifdef ESP8266
#include <ESP8266WebServer.h>
typedef  ESP8266WebServer ESPWebServer;
#else
#include <WebServer.h>
typedef  WebServer ESPWebServer;
#endif
