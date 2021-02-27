#include "Controller.hpp"
#define POT_PIN A0
#define GREEN_PIN 13
#define RED_PIN 9
Controller* arduino;
int trash_value=0;
void setup(){
  arduino = new Controller(GREEN_PIN, RED_PIN, POT_PIN);
  Serial.begin(9600);
}

void loop(){
  
  arduino->AvailableState();
  delay(2500);
  arduino->UnavailableState();
  delay(2500);
  /*if(arduino->getTrashLevel()!=trash_value){
    trash_value=arduino->getTrashLevel();
    Serial.println(trash_value);
  }*/
  Serial.println(arduino->getTrashLevel());
}
