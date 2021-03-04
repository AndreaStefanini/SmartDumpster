#ifndef _BLUETOOTH_
#define _BLUETOOTH_
#endif 



class Bluetooth {
    public:
        Bluetooth(int TX, int RX);
        void Setup();
    private:
        int tx;
        int rx;
        

};
