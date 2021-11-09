
#include <ESP8266WiFi.h>
#include "potenziometro.hpp"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "led.hpp"
#define rx 5
#define tx 4
#define POT 6
#define GREEN_PIN 7
#define RED_PIN 8
#define MAX_TRASH 100
led* green_led;
led* red_led;
//Potenziometro* pot;
//the status is set to true when the dumpster is available, false in the opposite case
int status = 1;
int notified =false;
int Trash=0;
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress server(192,168,1,9);
SoftwareSerial arSerial(rx,tx);
void setup(){
    //pot = new Potenziometro(POT);
    //green_led = new led(GREEN_PIN);
    //red_led = new led(RED_PIN);
    Serial.begin(9600);
    arSerial.begin(9600);
    WiFi.begin("Vodafone-Casa","Stefanini,217");
    Serial.println("Connecting...");
    while (WiFi.status()!= WL_CONNECTED) {
        delay(500);
        Serial.println("...");
    }
    Serial.print("Connected, acquired an IP Address:");
    Serial.println(WiFi.localIP());
    
}
      //la quantità di trash non è al massimo quindi siamo ancora a posto

void loop(){ 
    get_updates();
    Serial.println(Trash);
    if(status==1){
      
      if(Trash<MAX_TRASH){
        //green_led->SwitchOn();
        //red_led->SwitchOff();
        if(notified == 1){
          notified =0;
        }
        readSerial();
      }else{
        status=0;
        update_server_on_status ();
      }
      
    }else{
      if(notified==0){
        update_server_on_status();
      }
      //red_led->SwitchOn();
      //green_led->SwitchOff();
    }
}
void sendSerialMessage(String msg){
  arSerial.print(msg);
}
void readSerial(){
  const char* content;
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
          if(isdigit(atoi(content))){
            Trash+=atoi(content);
            Serial.println(Trash);
          }
          content=""; 
     }
}
//deve informare il server squando divento un available ma solo una volta
void update_server_on_status (){
    wfclient.connect(server,80);
    const char* url ="";
    client.begin(wfclient,url);
    client.addHeader("Content-Type", "application/json");
    StaticJsonDocument<256> doc;
    JsonObject object = doc.to<JsonObject>();
    object["Status"]= status;
    serializeJson(doc, jsonOutput);
    //Serial.println(jsonOutput);
 
    
     
    int httpCode = client.POST(jsonOutput);
    Serial.println(httpCode);
    if (httpCode>0 ){
        String payload = client.getString();
        Serial.println(payload);
    }
    client.end();
    wfclient.stop();
    notified=1;
}
int get_updates(){
    wfclient.connect(server,80);
    const char* url ="http://192.168.1.9/sd-service/get_server_status.php";
    client.begin(wfclient,url);
    client.addHeader("Content-Type", "text/plain");
    int httpCode = client.GET();
    
    if (httpCode>0 ){
        int payload = client.getString().toInt();
        if(payload != status){
          status = payload;
          Serial.println("non sono uguali");
        }
    }
    client.end();
    wfclient.stop();
    return 0;
}
