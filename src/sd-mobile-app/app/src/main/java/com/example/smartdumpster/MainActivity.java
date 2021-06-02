package com.example.smartdumpster;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;


import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.provider.Settings;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;

import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;


/**
 * TODO:
 *  request to turn on wifi DONE
 *  request to turn on bt DONE
 *  check the register, because the discovery doesn't return no new bluetooth devices
 *  use a BT library to manage the exchange of information
 *
 */
public class MainActivity extends AppCompatActivity {
    private TextView token;
    private String Token;
    private BluetoothChannel btChannel;
    private Button btn;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        if(btAdapter!= null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE),1);
        }
        checkWifi();

    }

    public void onStart() {
        super.onStart();
        try {
            ConnectToBTServer();
        } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
            bluetoothDeviceNotFound.printStackTrace();
        }
    }

    public void onStop() {
        super.onStop();

    }
    public void GetToken(View view){
        RequestQueue requestQ = Volley.newRequestQueue(this);
        JsonObjectRequest objectRequest = new JsonObjectRequest(Request.Method.GET,"https://dummy.restapiexample.com/api/v1/employee/1", null,
                response -> {
                    try {
                        Token  = (String) response.getJSONObject("data").get("employee_name");
                        token.setText(Token);

                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                },
                error -> token.setText(error.getMessage()));
        requestQ.add(objectRequest);
        //StringRequest stringQ = new StringRequest(Request.Method.GET, "http://dummy.restapiexample.com/api/v1/employee/1",  response -> token.setText(response), error -> token.setText("There was an error during comunication with the server"));
        //System.out.println(Token);

        btn = findViewById(R.id.throw_garbage);
        btn.setClickable(true);
    }

    /**
     *  this function uses the bluetooth channel to communicate
     * @param view
     */
    public void ThrowGarbage(View view) {
        btChannel.sendMessage(Token);
    }

    public void checkWifi(){
        ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo ni = cm.getActiveNetworkInfo();
        if(ni == null){
            Intent wifi = new Intent(Settings.ACTION_WIFI_SETTINGS);
            startActivityForResult(wifi,1);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
    private void ConnectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverTarget = BluetoothUtils.getPairedDeviceByName("SmartDumpster");
        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();

        new ConnectToBluetoothServerTask(serverTarget, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(BluetoothChannel channel) {
                TextView state = findViewById(R.id.btState);
                state.setText("connected");
                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener(){
                    @Override
                    public void onMessageReceived(String receivedMessage){
                        token.setText("");
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {

                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                TextView state = findViewById(R.id.btState);
                state.setText("not connected");
            }
        }).execute();
    }
}