#include "Arduino.hpp"

namespace controller{
    Arduino::Arduino(int GREEN_PIN, int RED_PIN){
        green_led = new led(GREEN_PIN);
        red_led = new led(RED_PIN);
    }
    void Arduino::AvailableState(){
        green_led->SwitchOn();
        red_led->SwitchOff();
    }
    void Arduino::UnavailableState(){
        green_led->SwitchOff();
        red_led->SwitchOn();
    }
}