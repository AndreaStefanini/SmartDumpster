package com.example.smartdumpster;


import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;

import android.content.Intent;
import android.content.IntentFilter;


import android.content.Context;

import java.util.HashSet;
import java.util.Set;



public class BluetoothManagerImpl implements BluetoothManager  {
    final private BluetoothAdapter bltAdapt;
    private final String BT_TARGET_NAME = "SmartDumpster";
    private Set<BluetoothDevice> newBluetoothDevice= new HashSet<>();
    public IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(BluetoothDevice.ACTION_FOUND.equals(intent.getAction())){
                BluetoothDevice device=intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                newBluetoothDevice.add(device);
            }
        }
    };

    public BluetoothManagerImpl(){
        bltAdapt = BluetoothAdapter.getDefaultAdapter();

    }


    @Override
    public boolean TurnOnBluetooth() {
        if(bltAdapt== null){
            return false;
        }
        return true;
    }

    @Override
    public void setUpBluetooth() {
        BluetoothDevice targetDevice = null;
        Set<BluetoothDevice> pairedList = bltAdapt.getBondedDevices();
        if(pairedList.size()>0){
            for (BluetoothDevice device : pairedList){
                if(device.getName().equals(BT_TARGET_NAME)){
                    targetDevice = device;

                }
            }
        }
        if(targetDevice!=null){
            System.out.print(targetDevice.getName());
        }else{
            if(!newBluetoothDevice.isEmpty()){

                for(BluetoothDevice device : newBluetoothDevice ) {
                    if (BT_TARGET_NAME == device.getName()) {

                    }
                }
            }else{
                System.out.println("Dispositivo non trovato");
            }
        }
    }

    @Override
    public IntentFilter getFilter() {
        return this.filter;
    }

    @Override
    public BroadcastReceiver getReceiver() {
        return this.receiver;
    }

    @Override
    public BluetoothAdapter getAdapter() {
        return this.bltAdapt;
    }

    @Override
    public void StopSearch() {
        bltAdapt.cancelDiscovery();
    }

    @Override
    public void StartSearch() {
        bltAdapt.startDiscovery();
    }
}
