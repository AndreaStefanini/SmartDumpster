package com.example.smartdumpster;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

import static android.content.ContentValues.TAG;

/**
 * this class is the connection thread, its duty is to connect to a device server (the BT module in out case)
 */
public class ConnectBTThread extends Thread {
    private BluetoothDevice device;
    private BluetoothSocket socket;
    private UUID uuid ;
    public ConnectBTThread(BluetoothDevice dev){
        this.device = dev;
        BluetoothSocket tmp = null;
        try {
            tmp = device.createRfcommSocketToServiceRecord(uuid);
        }catch (IOException e){
            Log.e(TAG, "Socket's creation failed", e);
        }
        socket = tmp;
    }
    @Override
    public void run(){
        try{
            socket.connect();
        }catch(IOException connectException){
            try{
                socket.close();
            }catch(IOException closeException){
                Log.e(TAG, "Could not close client socket",closeException);
            }
            return ;

        }
        //manageMyConnection(socket);
    }
    public void cancel(){
        try{
            socket.close();
        }catch(IOException e){
            Log.e(TAG, "Could not close client socket",e);
        }
    }
}
