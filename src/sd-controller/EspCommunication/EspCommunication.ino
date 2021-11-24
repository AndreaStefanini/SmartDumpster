
#include <ESP8266WiFi.h>
#include "potenziometro.hpp"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "led.hpp"
#include "MsgServiceBT.hpp"
#define rx 5
#define tx 4
#define POT A0
#define GREEN_PIN 2
#define RED_PIN 0
#define MAX_TRASH 100
led* green_led;
led* red_led;
Potenziometro* pot;
//the status is set to true when the dumpster is available, false in the opposite case
int status = 1;
int notified = 0;
int Trash = 0;
HTTPClient client;
WiFiClient wfclient;
char jsonOutput[128];
IPAddress server(192, 168, 1, 9);
MsgServiceBT *arSerial = new MsgServiceBT(rx, tx);
void setup() {
  pot = new Potenziometro(POT);
  green_led = new led(GREEN_PIN);
  red_led = new led(RED_PIN);
  arSerial->init();
  Serial.begin(9600);
  WiFi.begin("Vodafone-Casa", "Stefanini,217");
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  Serial.print("Connected, acquired an IP Address:");
  Serial.println(WiFi.localIP());

}
//la quantità di trash non è al massimo quindi siamo ancora a posto

void loop() {
  get_updates();
  if (status == 1) {

    if (Trash < MAX_TRASH) {
      green_led->SwitchOn();
      red_led->SwitchOff();
      if (notified == 1) {
        notified = 0;
      }
      read_arduino_serial();
    } else {
      status = 0;
      Serial.println("chiama per informare il server dello status attuale");
      update_server_on_status ();
    }

  } else {
    if (notified == 0) {
      update_server_on_status();
    }
    red_led->SwitchOn();
    green_led->SwitchOff();
  }
}

//deve informare il server squando divento un available ma solo una volta
void update_server_on_status () {
  wfclient.connect(server, 80);
  const char* url = "http://192.168.1.9/sd-service/update_status.php";
  client.begin(wfclient, url);
  client.addHeader("Content-Type", "application/json");
  DynamicJsonDocument doc(256);
  doc["State"] = status;
  serializeJson(doc, jsonOutput);



  int httpCode = client.POST(jsonOutput);
  Serial.println(httpCode);
  if (httpCode > 0 ) {
    String payload = client.getString();
  }
  client.end();
  wfclient.stop();
  notified = 1;
}
void read_arduino_serial() {
  if (arSerial->isMsgAvailable()) {
    String content = arSerial->receiveMsg()->getContent();
    Serial.print("Il contenuto della seriale: ");
    Serial.println(content);
    int weight = content.toInt();
    Trash += weight;
  }
}
int get_updates() {
  DynamicJsonDocument doc(256);
  wfclient.connect(server, 80);
  const char* url = "http://192.168.1.9/sd-service/get_server_status.php";
  client.begin(wfclient, url);
  client.addHeader("Content-Type", "text/plain");
  int httpCode = client.GET();

  if (httpCode > 0 ) {
    String payload = client.getString();
    deserializeJson(doc,payload);
    int rifiuti = doc["rifiuti"];
    int disponibilita = doc["disponibile"];
    if (disponibilita != status) {
      status = disponibilita;
      Serial.println("non sono uguali");
      
    }
    if (Trash != rifiuti) {
        Trash = rifiuti;
      }
  }
  client.end();
  wfclient.stop();
  return 0;
}
