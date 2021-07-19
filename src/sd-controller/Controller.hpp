#include "led.hpp"
#include "potenziometro.hpp"
#include "MsgServiceBT.hpp"

class Controller{
        public:
            Controller(int GREEN_PIN, int RED_PIN, int POT_PIN, int BT_RX, int BT_TX);
            void AvailableState(); 
            void UnavailableState();
            int getTrashLevel();
            String retrieve_message();              
        private:
            int number_of_trash;
            led* green_led;
            led* red_led;
            Potenziometro* trash_pot;
            MsgServiceBT* btService;
            String message;
            
};
