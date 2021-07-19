//momentaneamente tengo il codice separato, in caso lo mergo con il sd-controller 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>
#include "WiFi_Esp.hpp"
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress server(104,21,10,8);
void setup()
{
    Serial.begin(115200);
    //first i proceed by setting up the wifi by setting the wifi with begin, it automaticaly set it on station 
    WiFi.begin("Vodafone-Casa","Stefanini,217");
    Serial.println("Connecting...");
    while (WiFi.status()!= WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("Connected, acquired an IP Address:");
    Serial.println(WiFi.localIP());
}

void loop()
{
    wfclient.connect(server,8080);
    const char* token = "prova";
    const char* url ="http://jsonplaceholder.typicode.com/posts";
    client.begin(wfclient,url);
    client.addHeader("Content-Type", "application/json");
    StaticJsonDocument<256> doc;
    JsonObject object = doc.to<JsonObject>();
    object["token"]= token;
    serializeJson(doc, jsonOutput);
    Serial.println(jsonOutput);
 
    
     
    int httpCode = client.POST(String(jsonOutput));
    Serial.println(httpCode);
    if (httpCode>0 ){
        String payload = client.getString();
        Serial.println(payload);
    }
    client.end();
}