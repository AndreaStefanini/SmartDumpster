#include "Controller.hpp"

Controller::Controller(int GREEN_PIN, int RED_PIN){
        green_led = new led(GREEN_PIN);
        red_led = new led(RED_PIN);
}
void Controller::AvailableState(){
        green_led->SwitchOn();
        red_led->SwitchOff();
}
void Controller::UnavailableState(){
        green_led->SwitchOff();
        red_led->SwitchOn();
}
