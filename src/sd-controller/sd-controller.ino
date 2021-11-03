#include "Controller.hpp"
#include <SimpleTimer.h>
#define TRASH_C 9
#define TRASH_B 12
#define TRASH_A 13
#define SERVO 8
#define BT_TX 3
#define BT_RX 2
#define ESP_RX 5
#define ESP_TX 6
Controller* arduino;
int timerID=NULL;
boolean check=false;
SimpleTimer timer;

void closing_procedure(){
  timer.deleteTimer(timerID);
  timerID=NULL;
  arduino->close_lid();
  Serial.println("Il tempo per inserire il rifiuto all'interno del bidone è scaduto ti preghiamo di riprovare");
  arduino->send_response("timeout");

}
void setup(){
  Serial.begin(9600);
  arduino = new Controller(TRASH_A,TRASH_B,TRASH_C,BT_RX,BT_TX, ESP_RX, ESP_TX, SERVO ); 
}

void loop(){
    timer.run();
    String content = arduino->retrieve_message();
    delay(1000);
    if (content != ""){
      check=true;
      Serial.println(content);
      if(content.equals("A")){
        arduino->SelectTrashA();
        timerID = timer.setTimeout(20000,closing_procedure);
        arduino->open_lid();
      }else if(content.equals("B")){
        arduino->SelectTrashB();
        timerID = timer.setTimeout(20000,closing_procedure);  
        arduino->open_lid();
      }else if(content.equals("C")){
        arduino->SelectTrashC();
        timerID = timer.setTimeout(20000,closing_procedure);
        arduino->open_lid();
      }else if(isDigit(content.charAt(0))){
          arduino->close_lid();
          timer.deleteTimer(timerID);
          Serial.println("Un rifiuto aggiunto al bidone :)");
          arduino->send_response("ok");
          int weight = content.toInt();
          arduino->update_counter(weight);
      }else if(content.equals("delay")){
          timer.restartTimer(timerID);  
      }else{
        Serial.println("E' apparso un errore, durante la comunicazione");
      }
    }  
}
