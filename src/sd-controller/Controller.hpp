#include "led.hpp"
#include "servo_motore.hpp"
#include "MsgServiceBT.hpp"
#include <SoftwareSerial.h>
#define OPEN 180
#define CLOSE -180
 

class Controller{
        public:
            Controller(int TRASH_A,int TRASH_B,int TRASH_C,int BT_RX, int BT_TX,int ESP_RX,int ESP_TX, int SERVO);
            int getTrashLevel();
            String retrieve_message(); 
            void send_response(String response);
            void SelectTrashA();
            void SelectTrashB();
            void SelectTrashC();
            void open_lid();
            void close_lid();
            void update_counter(int weigth);
        private:
            servo_motore* servo;
            led* Trash_A;
            led* Trash_B;
            led* Trash_C;
            MsgServiceBT* btService;
            SoftwareSerial* espSerial;
            
};
