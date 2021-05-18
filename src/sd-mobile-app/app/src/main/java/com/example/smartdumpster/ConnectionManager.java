package com.example.smartdumpster;

import android.bluetooth.BluetoothSocket;
import android.net.ConnectivityManager;

import java.io.IOException;
import java.util.logging.Handler;

public class ConnectionManager {
    private BluetoothSocket socket;

    public ConnectionManager(BluetoothSocket soc){
        this.socket=soc;
    }
    void read() throws IOException {
        this.socket.getInputStream().read();
    }
    void write(String token) throws IOException {
        this.socket.getOutputStream().write(token.getBytes()) ;
    }

}
