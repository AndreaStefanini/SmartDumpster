//momentaneamente tengo il codice separato, in caso lo mergo con il sd-controller 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup()
{
    //first i proceed by setting up the wifi
    WiFi.begin("Vodafone-Casa","Stefanini,217");
    Serial.println("Connecting...");
    while (WiFi.Status()!= WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("Connected, acquired an IP Address:");
    Serial.println(WiFi.localIP());
}

void loop()
{
    
}