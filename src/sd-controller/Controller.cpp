#include "Controller.hpp"

Controller::Controller(int GREEN_PIN, int RED_PIN, int POT_PIN,int bt_tx, int bt_rx){
        green_led = new led(GREEN_PIN);
        red_led = new led(RED_PIN);
        trash_pot = new Potenziometro(POT_PIN);
        bt = new Bluetooth(bt_tx,bt_rx);
        //bt->Setup();
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
