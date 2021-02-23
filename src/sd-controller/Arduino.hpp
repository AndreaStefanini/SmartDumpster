#include "led.hpp"

namespace controller{
    class Arduino{
        public:
            Arduino(int GREEN_PIN, int RED_PIN);
            void AvailableState(); 
            void UnavailableState();
            
        private:
            int number_of_trash;
            led* green_led;
            led* red_led;
    };
};