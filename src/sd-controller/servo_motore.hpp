#ifndef _SERVO_MOTORE_
#define _SERVO_MOTORE_
#include <Servo.h>
#include <Arduino.h>


class servo_motore {
    public:
        servo_motore(int SERVO_PIN);
        void Position(int position);
    private:
        Servo servo;
};









#endif
