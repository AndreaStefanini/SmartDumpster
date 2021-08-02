#include "led.hpp"
#include <Arduino.h>
    led::led(int pin){
        led::LED_PIN=pin;
        pinMode(LED_PIN,OUTPUT);
    }
    int led::SwitchOn(){
        led::led_state=true;
        digitalWrite(led::LED_PIN,HIGH);
        return 0;
    }
    int led::SwitchOff(){
        led::led_state=false;
        digitalWrite(led::LED_PIN,LOW);
        return 0;
    }
    bool led::isSwitchedOn(){
        return led::led_state;
    }
