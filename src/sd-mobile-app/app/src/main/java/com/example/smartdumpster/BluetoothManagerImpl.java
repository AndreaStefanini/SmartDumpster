package com.example.smartdumpster;


import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;

import android.content.Intent;
import android.content.IntentFilter;


import android.content.Context;
import android.net.wifi.p2p.WifiP2pManager;

import java.util.HashSet;
import java.util.Observable;
import java.util.Observer;
import java.util.Set;
import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;


public class BluetoothManagerImpl implements BluetoothManager {
    final private BluetoothAdapter bltAdapt;
    private final String BT_TARGET_NAME = "SmartDumpster";
    private IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
    private MyReceiver receiver;
    BluetoothDevice targetDevice = null;
    final UUID uuid = UUID.randomUUID();
    private BluetoothChannel btChannel;



    public BluetoothManagerImpl() {
        bltAdapt = BluetoothAdapter.getDefaultAdapter();
    }


    @Override
    public boolean TurnOnBluetooth() {
        if (bltAdapt == null) {
            return false;
        }
        return true;
    }

    @Override
    public void setUpBluetooth() {
        Set<BluetoothDevice> pairedList = bltAdapt.getBondedDevices();
        if (pairedList.size() > 0) {
            for (BluetoothDevice device : pairedList) {
                if (device.getName().equals(BT_TARGET_NAME)) {
                    targetDevice = device;
                    this.StopSearch();
                    startConnectionToServer();
                }
            }
        }
        if (targetDevice != null) {
            System.out.print(targetDevice.getName());
        } else {
            System.out.println("trovato");
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

    @Override
    public void startConnectionToServer() {
        new ConnectToBluetoothServerTask(targetDevice,uuid,new ConnectionTask.EventListener(){

            @Override
            public void onConnectionActive(BluetoothChannel channel) {
                btChannel = channel;
            }

            @Override
            public void onConnectionCanceled() {

            }
        });
    }

    @Override
    public void sendMessage(String message) {
        btChannel.sendMessage(message);
    }

}