#include "potenziometro.hpp"
#include "Arduino.h"
Potenziometro::Potenziometro(int pot_pin){
    pin= pot_pin;
    pinMode(pin,INPUT);
}
int Potenziometro::getValue(){
    return value;
}
void Potenziometro::readPotenziometro(){
    value = analogRead(pin);
}
