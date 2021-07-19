#include "WiFi_Esp.hpp"

void wifi::Setup_WIFI(){
    WiFi.begin(SSID,Password);
    while (WiFi.status()!= WL_CONNECTED){
        
    }

}
void wifi::HTTP_Req(char* token){
    wfclient.connect(server,8080);
    client.begin(wfclient,"http://echo.jsontest.com/");
    client.addHeader("Content-Type", "application/json");
    StaticJsonDocument<69> doc;
    JsonObject& obj = doc.to<JsonObject>();
    obj["token"] = token;
    serializeJson(doc,jsonOutput);
    int httpCode = client.POST(String(jsonOutput));
    if (httpCode>0 ){
        String payload = http.getString();
    
    }
    if(payload=="true"){
        //devo ritornare positivo al controllore che dovrá informare il telefono e procedere con il potenziometro
    }else{
        //devo informare l'utente da telefono che il token non è giusto che quindi deve ritentare
    }
    wfclient.stop();
    client.end();
}