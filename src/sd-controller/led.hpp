namespace controller{
    class led{
        public:
            led(int pin);
            int SwitchOn();
            int SwitchOff();
            bool isSwitchedOn();
        private:
            bool led_state;
            int LED_PIN;
    };
}