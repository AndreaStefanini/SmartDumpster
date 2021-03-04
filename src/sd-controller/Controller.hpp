#include "led.hpp"
#include "potenziometro.hpp"
#include "BluetoothAdapt.hpp"

class Controller{
        public:
            Controller(int GREEN_PIN, int RED_PIN, int POT_PIN, int bt_tx, int bt_rx);
            void AvailableState(); 
            void UnavailableState();
            int getTrashLevel();   
        private:
            int number_of_trash;
            led* green_led;
            led* red_led;
            Potenziometro* trash_pot;
            Bluetooth* bt;
};
