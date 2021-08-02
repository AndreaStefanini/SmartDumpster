///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //NELLE COMUNICAZIONI SERIALI TRA ARDUINO E ESP UTILIZZERO' DUE LETTERE PER PERMETTERE AI DUE DISPOSITIVI DI RICONOSCERE COSA E' STATO INVIATO
                                                        //I+CODICE => IMMONDIAZIA
                                                        //T+CODICE => TOKEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include "potenziometro.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#define rx 4
#define tx 5
int Trash =0;
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress server(104,21,10,8);
SoftwareSerial arSerial(rx,tx);
void setup()
{
    Serial.begin(9600);
    arSerial.begin(9600);
    WiFi.begin("your-wifi","your-passwprd");
    Serial.println("Connecting...");
    while (WiFi.status()!= WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("Connected, acquired an IP Address:");
    Serial.println(WiFi.localIP());
    
}

void loop(){      
    readSerial();
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
          if(content.substring(0,1)=="I"){
            int newTrash=content.substring(1).toInt();
            if (newTrash!= Trash){
              Trash=newTrash;
            }
          }else if(content.substring(0,1)=="T"){
            content=content.substring(1);
            connection(content);
          }
          content=""; 
     }
}
