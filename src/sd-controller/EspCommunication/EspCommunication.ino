///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //NELLE COMUNICAZIONI SERIALI TRA ARDUINO E ESP UTILIZZERO' DUE LETTERE PER PERMETTERE AI DUE DISPOSITIVI DI RICONOSCERE COSA E' STATO INVIATO
                                                        //I+CODICE => IMMONDIAZIA
                                                        //T+CODICE => TOKEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#define rx 4
#define tx 5
int Trash =0;
ESP8266WebServer server(80);
String content;
char letter;
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress POSTserver(104,21,10,8);
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
    server.on("/", handleOnConnect);
    server.onNotFound(handleNotFound);
    server.on("/empty", handleEmptyTrash);
    server.on("/refresh", handleRefresh);
    server.begin();
    
}

void loop(){ 
    server.handleClient();     
    readSerial();
}

void connection(String token){
 
    wfclient.connect(POSTserver,80);
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

void handleOnConnect(){
 
  server.send(200,"text/html",SendHTML(Trash));
}
void handleEmptyTrash(){
  
  String trash_update="0";
  sendSerialMessage(trash_update);
  server.send(200,"text/html",SendHTML(0));
}
String SendHTML(int trash){
  String page="<!DOCTYPE html>\n<html>\n";
  page+= "<head><meta name=\"viewport\" content=\"device-width, initial-scale=1.0, user-scalable=no\">\n";
  page+= "<title> SmartDumpster</title>\n";
  page+="<style>\n";
  page+=".title{text-align: center;}\n";
  page+=".button_nonavail {background-color:grey; border-radius:5px; padding: 17px 22px; color:white; text-decoration: none;}\n";
  page+=".button_avail {background-color: green; border-radius:5px; padding: 17px 22px; color:white; text-decoration: none;}\n";
  page+=".trash {display: inline-block;}\n";
  page+="</style>\n";
  page+="<script>\n";
  page+="setInterval(fetch(\"/refresh\").then(function(response) {return response.json();}).then(function(data) {document.getElementById(\"trash\").innerHTML=\"Trash level:\"+ data[\"trash\"];}),10000);\n";
  page+="</script>\n";
  page+="</head>\n";
  page+="<body>\n";
  page+="<h1 class=\"title\"> SmartDumpster </h1>\n";
  page+="<h3 class=\"title\"> Admin Interface </h3>\n";

  if(trash == 0){
    page+="<a class=\"button_nonavail\" href=\"/empty\">Empty</a> <p class=\"trash\" id=\"trash\">Trash level:0</p>\n";
  }else{
    page+="<a class=\"button_avail\" href =\"/empty\">Empty</a> <p class=\"trash\" id=\"trash\">Trash level:</p>";
    page+=String(trash);
  }
  page+="</body>\n";
  page+="</html>\n";
  return page;
}
void sendSerialMessage(String msg){
  arSerial.print(msg);
}
void readSerial(){
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
              handleOnConnect();
            }
            
          }else if(content.substring(0,1)=="T"){
            content=content.substring(1);
            connection(content);
            
          }
          content=""; 
     }
}
void handleNotFound(){
   server.send(404, "text/plain", "NOT FOUND");
}
void handleRefresh(){
  String msg = "{\"trash\":";
  msg+=String(Trash);
  msg+="}";
  StaticJsonDocument<256> doc;
  JsonObject object = doc.to<JsonObject>();
  object["trash"]= Trash;
  serializeJson(doc, jsonOutput);
  server.send(200,"text/plain",String(jsonOutput));
}
