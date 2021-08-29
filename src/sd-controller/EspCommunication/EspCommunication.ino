
#include <ESP8266WiFi.h>
#include "potenziometro.hpp"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "led.hpp"
#define rx 4
#define tx 5
#define POT 6
#define GREEN_PIN 7
#define RED_PIN 8
#define MAX_TRASH 20
led* green_led;
led* red_led;
Potenziometro* pot;
int Trash =0;
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress server(104,21,10,8);
SoftwareSerial arSerial(rx,tx);
void setup()
{
    pot = new Potenziometro(POT);
    green_led = new led(GREEN_PIN);
    red_led = new led(RED_PIN);
    Serial.begin(9600);
    arSerial.begin(9600);
    WiFi.begin("your-wifi","your-password");
    Serial.println("Connecting...");
    while (WiFi.status()!= WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("Connected, acquired an IP Address:");
    Serial.println(WiFi.localIP());
    
}

void loop(){ 
    if(Trash<MAX_TRASH){
      green_led->SwitchOn();
      red_led->SwitchOff();
      readSerial();  
    }else{
      green_led->SwitchOn();
      red_led->SwitchOff();
    }
    
}

/*void connection(String token){
 
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
    
}*/


void sendSerialMessage(String msg){
  arSerial.print(msg);
}
void readSerial(){
  String content;
  char letter;
  while(arSerial.available()>0){
        char letter = arSerial.read();
        if(letter != '\r' && letter!='\n'){
          content+=letter;
        }     
     }
     // a delay was inserted because the serial empty itself faster than the read function to complete,
     //so it create situations where the read was able to read only the first character

     delay(1000);
     if(content!=""){
          Serial.println("il contenuto della seriale:");
          Serial.println(content);
          if(content=="1"){
            Trash++;
            update_server();
          }
          content=""; 
     }
}
void update_server(){
  wfclient.connect(server,80);
    const char* url ="http://jsonplaceholder.typicode.com/posts";
    client.begin(wfclient,url);
    client.addHeader("Content-Type", "application/json");
    StaticJsonDocument<256> doc;
    JsonObject object = doc.to<JsonObject>();
    object["trash"]= Trash;
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
