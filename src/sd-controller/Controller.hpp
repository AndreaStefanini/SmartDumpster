#include "led.hpp"
#include "potenziometro.hpp"
#include "MsgServiceBT.hpp"
#include <SoftwareSerial.h>

 

class Controller{
        public:
            Controller(int GREEN_PIN, int RED_PIN, int POT_PIN, int BT_RX, int BT_TX, int ESP_RX, int ESP_TX);
            void AvailableState(); 
            void UnavailableState();
            int getTrashLevel();
            String retrieve_message();
            bool confirm_token(String token); 
            void send_response(String response);             
        private:
            int number_of_trash;
            led* green_led;
            led* red_led;
            Potenziometro* trash_pot;
            MsgServiceBT* btService;
            SoftwareSerial* espSerial;
            
};
