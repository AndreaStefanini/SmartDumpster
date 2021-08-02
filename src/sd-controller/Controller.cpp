#include "Controller.hpp"

Controller::Controller(int TRASH_A, int TRASH_B,int TRASH_C,int BT_RX,int BT_TX,int ESP_RX,int ESP_TX, int SERVO){
        Trash_A = new led(TRASH_A);
        Trash_B = new led(TRASH_B);
        Trash_C = new led(TRASH_C);
        btService = new MsgServiceBT(BT_RX,BT_TX);
        espSerial = new SoftwareSerial(ESP_RX, ESP_TX);
        servo = new servo_motore(SERVO);
        espSerial->begin(9600);
        btService->init();     
}

String Controller::retrieve_message(){
        String message = btService->receiveMsg()->getContent();
        return message;   
}

void Controller::send_response(String response){
    Serial.println("la parola è:");
    Serial.println(response);
    if(response.equals("ping")){
      Msg* msg = new Msg("PONG");
      btService->sendMsg(*msg); 
    }
    Msg* msg = new Msg("it's not ping");
    btService->sendMsg(*msg);
}
void Controller::SelectTrashA(){
  Trash_A->SwitchOn();
  Trash_B->SwitchOff();
  Trash_C->SwitchOff();
}
void Controller::SelectTrashB(){
  Trash_A->SwitchOff();
  Trash_B->SwitchOn();
  Trash_C->SwitchOff();
}
void Controller::SelectTrashC(){
  Trash_A->SwitchOff();
  Trash_B->SwitchOff();
  Trash_C->SwitchOn();
}
void Controller::open_lid(){
  servo->Position(OPEN);
}
void Controller::close_lid(){
  if(Trash_A->isSwitchedOn()){
    Trash_A->SwitchOff();
  }
  if(Trash_B->isSwitchedOn()){
    Trash_B->SwitchOff();
  }
  if(Trash_C->isSwitchedOn()){
    Trash_C->SwitchOff();
  }
  servo->Position(CLOSE);
}
