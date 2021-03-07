package com.example.smartdumpster;

import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import java.util.HashSet;
import java.util.Observable;
import java.util.Observer;
import java.util.Set;

public class MyReceiver extends BroadcastReceiver {
    private Set<BluetoothDevice> newBluetoothDevice= new HashSet<>();
    Observable o;


    public MyReceiver(Observer ob){
        this.o.addObserver(ob);

    }
    @Override
    public void onReceive(Context context, Intent intent) {
        if(BluetoothDevice.ACTION_FOUND.equals(intent.getAction())){
            BluetoothDevice device=intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
            newBluetoothDevice.add(device);
            o.notifyObservers();
        }
    }
    public Set<BluetoothDevice> getNewDevices(){
        return this.newBluetoothDevice;
    }
}
