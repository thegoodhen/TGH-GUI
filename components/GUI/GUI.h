#include "GUIElement.h"
#include "Arduino.h"
#include "ESPAsyncWebServer.h"
#include "GUIContainer.h"
#include "GUIEndpoint.h"
class GUI : public GUIContainer
{
public:
    int add(IHTMLSerializable* _ge) override;
    static GUI* begin(AsyncWebServer* _server=NULL,String str="");
    //int sendHTML(AsyncWebServerRequest* _request) const override;
    String getHeader() const override;
    String getFooter() const override;
    //int getHTML(char* _outputStr, uint32_t _maxLen) const override;
    String getHTML() const override;
    String getId() const override;
    static GUI* getInstance();

private:
    GUI(); // Private copy constructor and assignment operator to prevent copying
    GUI(const GUI &) = delete;
    GUI &operator=(const GUI &) = delete;
    static GUI* instance;
    void registerEndpoint(GUIEndpoint* _ge);
    AsyncWebServer* webserver;
    static void webSocketEventHandler(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
};