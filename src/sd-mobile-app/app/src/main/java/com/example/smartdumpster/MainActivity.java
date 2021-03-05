package com.example.smartdumpster;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;


import android.bluetooth.BluetoothAdapter;
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
    private Button btn;
    private BluetoothManager bt;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bt = new BluetoothManagerImpl();
        registerReceiver(bt.getReceiver(), bt.getFilter());


    }

    public void onStart() {
        super.onStart();
        if(bt.TurnOnBluetooth()){
            if(!bt.getAdapter().isEnabled()){
                Intent blueOn = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(blueOn, 1);
            }
            while(!bt.getAdapter().isEnabled()){}
            bt.StopSearch();
            bt.setUpBluetooth();
        }else{
            AlertDialog dialog = new AlertDialog.Builder(this)
                    .setTitle("Bluetooth is missing")
                    .setMessage("This device seems not having the bluetooth, it might be a bug, in that case reboot the system, otherwise you need to get a bluetooth adapter.")
                    .setPositiveButton("Ok", (dialog1, which) -> {
                        dialog1.dismiss();
                        System.exit(0);
                    })
                    .create();
        }

        checkWifi();


        token = findViewById(R.id.token);

    }

    public void onStop() {
        super.onStop();
        bt.StopSearch();
        unregisterReceiver(bt.getReceiver());
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

    public void ThrowGarbage(View view) {
    }
    public void checkWifi(){
        ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo ni = cm.getActiveNetworkInfo();
        if(ni == null){
            Intent wifi = new Intent(Settings.ACTION_WIFI_SETTINGS);
            startActivityForResult(wifi,1);
        }
    }

}