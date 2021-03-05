package com.example.smartdumpster;

import android.bluetooth.BluetoothAdapter;
import android.content.BroadcastReceiver;
import android.content.IntentFilter;

import androidx.appcompat.app.AppCompatActivity;

public interface BluetoothManager {
    boolean TurnOnBluetooth();
    void setUpBluetooth();
    IntentFilter getFilter();
    BroadcastReceiver getReceiver();
    BluetoothAdapter getAdapter();
    void StopSearch();
    void StartSearch();
}
