#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>
#include <SoftwareSerial.h>
#define rx 4
#define tx 5
String content;
char letter;
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress server(104,21,10,8);
SoftwareSerial arSerial(rx,tx);
void ConnectWifi(){
    WiFi.begin("Vodafone-Casa","Stefanini,217");
    Serial.println("Connecting...");
    while (WiFi.status()!= WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("Connected, acquired an IP Address:");
    Serial.println(WiFi.localIP());
}
void setup()
{
    Serial.begin(9600);
    arSerial.begin(9600);
    ConnectWifi();
}

void loop()
{ 
    
    while(arSerial.available()>0){
        char letter = arSerial.read();
        if(letter != '\r'){
          content+=letter;
        }     
     }
     // a delay was inserted because the serial empty itself faster than the read function to complete, so it create situations where the read was able to read only the first character
     delay(1000);
     if(content!=""){
          Serial.println("il contenuto della seriale:");
          Serial.println(content);
          connection(content);
          content=""; 
     }
        
}

void connection(String token){
 
    wfclient.connect(server,80);
    const char* url ="http://jsonplaceholder.typicode.com/posts";
    client.begin(wfclient,url);
    client.addHeader("Content-Type", "application/json");
    StaticJsonDocument<256> doc;
    JsonObject object = doc.to<JsonObject>();
    object["token"]= token;
    serializeJson(doc, jsonOutput);
    //Serial.println(jsonOutput);
 
    
     
    int httpCode = client.POST(String(jsonOutput));
    Serial.println(httpCode);
    if (httpCode>0 ){
        String payload = client.getString();
        Serial.println(payload);
    }
    client.end();
    wfclient.stop();
    
}
