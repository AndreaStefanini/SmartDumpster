#include "led.hpp"


class Controller{
        public:
            Controller(int GREEN_PIN, int RED_PIN);
            void AvailableState(); 
            void UnavailableState();   
        private:
            int number_of_trash;
            led* green_led;
            led* red_led;
};
