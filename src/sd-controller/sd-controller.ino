#include "Controller.hpp"
#include <SimpleTimer.h>
#define TRASH_C 9
#define TRASH_B 12
#define TRASH_A 13
#define SERVO 8
#define BT_TX 2
#define BT_RX 3
#define ESP_RX 5
#define ESP_TX 6
Controller* arduino;
SimpleTimer timer;
void setup(){
  Serial.begin(9600);
  arduino = new Controller(TRASH_A,TRASH_B,TRASH_C,BT_RX,BT_TX, ESP_RX, ESP_TX, SERVO ); 
}

void loop(){
  if(timer.isReady()){
    arduino->close_lid();
    timer.reset();
    Serial.println("Il tempo per inserire il rifiuto all'interno del bidone è scaduto ti preghiamo di riprovare");
  }
    String content = arduino->retrieve_message();
    delay(1000);
    
    if (content != ""){
      Serial.println(content);
      if(content.equals("A")){
        arduino->SelectTrashA();
        timer.setInterval(10000);
        arduino->open_lid();
      }else if(content.equals("B")){
        arduino->SelectTrashB();
        timer.setInterval(10000);
        arduino->open_lid();
      }else if(content.equals("C")){
        arduino->SelectTrashC();
        timer.setInterval(10000);
        arduino->open_lid();
      }else if(content.equals("1")){
          arduino->close_lid();
          timer.reset();
          Serial.println("Un rifiuto aggiunto al bidone :)");
      }else{
        Serial.println("An error occured while receiving a message... please try again");   
      }
    }  
}
