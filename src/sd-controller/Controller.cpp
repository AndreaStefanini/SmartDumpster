#include "Controller.hpp"

Controller::Controller(int GREEN_PIN, int RED_PIN, int POT_PIN, int BT_RX, int BT_TX, int ESP_RX, int ESP_TX){
        green_led = new led(GREEN_PIN);
        red_led = new led(RED_PIN);
        trash_pot = new Potenziometro(POT_PIN);
        btService = new MsgServiceBT(BT_RX,BT_TX);
        espSerial = new SoftwareSerial(ESP_RX, ESP_TX);
        espSerial->begin(9600);
        //esp = new wifi();
        //esp->Setup_WIFI();
        btService->init();
        
}
void Controller::AvailableState(){
        green_led->SwitchOn();
        red_led->SwitchOff();
}
void Controller::UnavailableState(){
        green_led->SwitchOff();
        red_led->SwitchOn();
}
int Controller::getTrashLevel(){
        trash_pot->readPotenziometro();
        return trash_pot->getValue();
}
String Controller::retrieve_message(){
        String message = btService->receiveMsg()->getContent();
        return message;
        
        
}
bool Controller::confirm_token(String token){
       Serial.println("mando all'esp il token");
       Serial.println(token);
       espSerial->print(token);
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
