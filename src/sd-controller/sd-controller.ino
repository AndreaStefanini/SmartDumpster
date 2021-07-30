#include "Controller.hpp"
#define POT_PIN A5
#define GREEN_PIN 9
#define RED_PIN 13
#define BT_TX 2
#define BT_RX 3
#define ESP_RX 5
#define ESP_TX 6
Controller* arduino;
int trash_value=0;
void setup(){
  Serial.begin(9600);
  arduino = new Controller(GREEN_PIN, RED_PIN, POT_PIN,BT_RX,BT_TX, ESP_RX, ESP_TX ); 
}

void loop(){
  int new_trash = arduino->getTrashLevel();
  delay(50);
  if(trash_value!=new_trash){
    trash_value=new_trash;
    arduino->sendTrash_level(trash_value);   
    Serial.println(trash_value);
  }
  if(trash_value<31){
    arduino->AvailableState();
    String content = arduino->retrieve_message();
    if (content != ""){
      Serial.println(content);
      
      arduino->send_response(content);
      arduino->confirm_token(content);
    }
  }else{
    arduino->UnavailableState();
  }
  
  String request = arduino->retrieve_request();
  if(request=="I"){
    Serial.print("richiesta quantità di rifiuti");
    //arduino->sendTrash_level(trash_value);
  }
  
  
}
