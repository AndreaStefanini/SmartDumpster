#include "WiFi_Esp.hpp"

void wifi::Setup_WIFI(){
    WiFi.begin(SSID,Password);
    while (WiFi.status()!= WL_CONNECTED){
        
    }

}
void wifi::HTTP_Req(char* token){
    client.begin("http://echo.jsontest.com/");
    client.addHeader("Content-Type", "application/json");
    StaticJsonBuffer<69> jsonBuffer;
    char json[] = "{\"token\":\+ token +\"}";
    JsonObject& root = jsonBuffer.parseObject(json);
    if(!root.success()) {
        Serial.println("parseObject() failed");
    } else {
        Serial.println("JSON OK");
    }
    String data;
    root.printTo(data);
    int httpCode = client.POST(data);
    if (httpCode>0 ){
        String payload = http.getString();
        Serial.println(payload);
    }
}