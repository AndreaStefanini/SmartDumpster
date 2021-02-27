#include "led.hpp"
#include "potenziometro.hpp"

class Controller{
        public:
            Controller(int GREEN_PIN, int RED_PIN, int POT_PIN);
            void AvailableState(); 
            void UnavailableState();
            int getTrashLevel();   
        private:
            int number_of_trash;
            led* green_led;
            led* red_led;
            Potenziometro* trash_pot;
};
