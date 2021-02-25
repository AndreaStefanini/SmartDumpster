#include "Controller.hpp"

#define GREEN_PIN 13
#define RED_PIN 9
Controller* arduino;
void setup(){
  arduino = new Controller(GREEN_PIN, RED_PIN);
}

void loop(){
  arduino->AvailableState();
  delay(5000);
  arduino->UnavailableState();
  delay(5000);
}
