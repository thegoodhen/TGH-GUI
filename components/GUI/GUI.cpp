#include "GUI.h"
#include "GUIElement.h"
#include "ESPAsyncWebServer.h"
#include "Arduino.h"

GUI *GUI::instance = nullptr;

GUI *GUI::begin(AsyncWebServer *_server, String _path)
{
    if (_server == NULL)
    {
        _server = new AsyncWebServer(80);
    }
    if (_path == "")
    {
        _path = "/";
    }
    AsyncWebSocket* ws = new AsyncWebSocket("/ws");
    GUIEndpoint* defaultEndpoint=new GUIEndpoint(_path);
    GUI* theInstance=getInstance();
    theInstance->webserver=_server;
    theInstance->add(defaultEndpoint);
    ws->onEvent(webSocketEventHandler);
    _server->addHandler(ws);
    _server->begin();
    return theInstance;
}

String GUI::getHTML() const
{
    return "";
}

String GUI::getId() const
{
    return "GUI";
}

GUI::GUI()
{
}

void GUI::registerEndpoint(GUIEndpoint* _ge)
{
    String path=_ge->getPath();
    webserver->on(path.c_str(), HTTP_GET, [_ge](AsyncWebServerRequest *request)
                { 

                AsyncWebServerResponse *response = request->beginChunkedResponse("text/html", [_ge](uint8_t *buffer, size_t maxLen, size_t index) -> size_t {
                        return _ge->getHTMLSubstring(buffer,maxLen,index);
                        });
                response->addHeader("Server","ESP Async Web Server");
                request->send(response);
                }
                );

}

int GUI::add(IHTMLSerializable *_ge)
{
    if (_ge->getType() == "ENDPOINT")
    {
        GUIContainer::add(_ge); 
        registerEndpoint((GUIEndpoint*)_ge);
    }
    else
    {
        GUIContainer *gc = (GUIContainer *)(this->find("ENDPOINT_/"));
        if (gc)
        {
            gc->add(_ge);
        }
    }
    return 0;
}
String GUI::getHeader() const
{
    return "";
}
String GUI::getFooter() const
{
    return "";
}

GUI *GUI::getInstance()
{
    if (instance == NULL)
    {
        instance = new GUI();
    }
    return instance;
}


void GUI::webSocketEventHandler(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
    printf("Hello!\n");
    return;
    
  if(type == WS_EVT_CONNECT){
    //client connected
    printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  } else if(type == WS_EVT_DISCONNECT){
    //client disconnected
    printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_ERROR){
    //error was received from the other end
    printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_PONG){
    //pong message was received (in response to a ping request maybe)
    printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } else if(type == WS_EVT_DATA){
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len){
      //the whole message is in a single frame and we got all of it's data
      printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT)?"text":"binary", info->len);
      if(info->opcode == WS_TEXT){
        data[len] = 0;
        printf("%s\n", (char*)data);
      } else {
        for(size_t i=0; i < info->len; i++){
          printf("%02x ", data[i]);
        }
        printf("\n");
      }
      if(info->opcode == WS_TEXT)
        client->text("I got your text message");
      else
        client->binary("I got your binary message");
    } else {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if(info->index == 0){
        if(info->num == 0)
          printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT)?"text":"binary");
        printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
      }

      printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT)?"text":"binary", info->index, info->index + len);
      if(info->message_opcode == WS_TEXT){
        data[len] = 0;
        printf("%s\n", (char*)data);
      } else {
        for(size_t i=0; i < len; i++){
          printf("%02x ", data[i]);
        }
        printf("\n");
      }

      if((info->index + len) == info->len){
        printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
        if(info->final){
          printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT)?"text":"binary");
          if(info->message_opcode == WS_TEXT)
            client->text("I got your text message");
          else
            client->binary("I got your binary message");
        }
      }
    }
  }
}