#include <stdio.h>
#include "GUI.h"
#include "Arduino.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "nvs_flash.h"
#include "Button.h"

//AsyncWebServer server(80);

const char *ssid = "TGH_network";
const char *password = "r0ut3rp@$$";

const char *PARAM_MESSAGE = "message";

void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

extern "C"
{
    void app_main(void)
    {
        Serial.begin(115200);
        Serial.println("KVA KVA");
        nvs_flash_init();
        // digitalWrite(4, HIGH);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        if (WiFi.waitForConnectResult() != WL_CONNECTED)
        {
            Serial.printf("WiFi Failed!\n");
            return;
        }

        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        /*
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
  request->send(200, "text/plain", "Hello, world");
                  });
                  */

        //server.onNotFound(notFound);
        GUI* theGUI=GUI::begin();
        Button* b=new Button("BTN","SLEPICE");
        Button* b2=new Button("BTN2","KOKODAK");
        GUIEndpoint* ge=new GUIEndpoint("/slepice");
        ge->add(b2);
        theGUI->add(b);
        theGUI->add(ge);
        

        //server.begin();
        int i=0;
        while (1)
        {
            //printf("%d\n",theGUI->getHTMLLength());
            char outBuff[1];
            int len=theGUI->getHTMLSubstring((uint8_t*)outBuff,1,i);
            //printf("%c\n",outBuff[0]);
            //printf("len: %d\n",len);
            i++;
            delay(100);
        }
    }
}
