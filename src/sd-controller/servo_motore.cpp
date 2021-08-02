#include "servo_motore.hpp"


servo_motore::servo_motore(int SERVO_PIN){
    servo.attach(SERVO_PIN);
}
void servo_motore::Position(int position){
    servo.write(position);
}
