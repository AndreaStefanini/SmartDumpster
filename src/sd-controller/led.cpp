#include "led.hpp"
namespace controller{
    led::led(int pin){
        led::LED_PIN=pin;
    }
    int led::SwitchOn(){
        led::led_state=true;
        //comando di arduino per accendere il led
        return 0;
    }
    int led::SwitchOff(){
        led::led_state=false;
        //comando di arduino per spegnere il led
        return 0;
    }
    bool led::isSwitchedOn(){
        return led::led_state;
    }
}
