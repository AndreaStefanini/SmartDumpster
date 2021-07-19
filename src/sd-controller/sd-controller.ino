#include "Controller.hpp"
#define POT_PIN A0
#define GREEN_PIN 13
#define RED_PIN 9
#define BT_TX 2
#define BT_RX 3
Controller* arduino;
int trash_value=0;
void setup(){
  Serial.begin(9600);
  
  arduino = new Controller(GREEN_PIN, RED_PIN, POT_PIN,BT_RX,BT_TX ); 
}

void loop(){
  String content = arduino->retrieve_message();
  if (content != ""){
    Serial.println(content);
  }
  /*arduino->AvailableState();
  delay(2500);
  arduino->UnavailableState();
  delay(2500);
  if(arduino->getTrashLevel()!=trash_value){
    trash_value=arduino->getTrashLevel();
    //Serial.println(trash_value);
  }*/
}
