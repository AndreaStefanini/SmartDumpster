#ifndef _POTENZIOMETRO_
#define _POTENZIOMETRO_
#endif

class Potenziometro{
    public:
        Potenziometro(int pot_pin);
        int getValue();
        void readPotenziometro();
    private:
        int pin;
        int value=0;

};
