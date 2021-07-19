#ifndef __WIFI_ESP__
#define __WIFI_ESP__ 
#endif
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Arduino.h"
#include <ArduinoJson.h>

    class wifi {
        private:
            const char* SSID ="Vodafone-Casa";
            const char* Password = "Stefanini,217";
            HTTPClient client;
            const IpAddress server(104,21,10,8);
            char jsonOutput[128];
            WiFiClient wfclient;
        public:
            void Setup_WIFI();
            void Token_Confermation(char* token);
};

