#include "BluetoothAdapt.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

                                                                  
Bluetooth::Bluetooth(int TX, int RX){
    rx=RX;
    tx=TX;
}
void Bluetooth::Setup(){
    

    btChannel.begin(38400);
    btChannel.print("AT+NAME");
    delay(1000);
    btChannel.print("AT+NAMEisi16");
    delay(1000);
    btChannel.print("AT+ADDR");
    delay(1000);
    btChannel.print("AT+ROLE=0");
    delay(1000);
    
}
