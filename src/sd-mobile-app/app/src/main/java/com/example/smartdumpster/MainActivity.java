package com.example.smartdumpster;

import androidx.appcompat.app.AppCompatActivity;


import android.app.AlertDialog;
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
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.google.android.material.textfield.TextInputEditText;

import org.json.JSONException;

import java.util.TimerTask;
import java.util.UUID;
import 	java.util.Timer;

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
 *  check the register, because the discovery doesn't return no new bluetooth devices DONE
 *  use a BT library to manage the exchange of information DONE
 *
 */
public class MainActivity extends AppCompatActivity {
    private TextView token;
    private String Token;
    private BluetoothChannel btChannel;
    private Button btn;
    private EditText t;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        if(btAdapter!= null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE),1);
        }
        checkWifi();
        token = findViewById(R.id.token);
        t= findViewById(R.id.quant_trash);
        btn = findViewById(R.id.throw_garbage);

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

    /**
     * this function send an http request to a server in order to obtain a token
     * @param view
     */
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


        while(btChannel==null && token.getText().length()==0){}

    }

    /**
     *  this function uses the bluetooth channel to communicate a token to the bluetooth module
     * @param view
     */
    public void ThrowGarbage(View view) {
        String value = t.getText().toString();
        if(!value.equals(null) && !value.isEmpty()){
            int weight =Integer.parseInt(t.getText().toString());
            System.out.println(weight);
            btChannel.sendMessage(String.valueOf(weight));
            btn.setEnabled(false);
            t.setText("");
            RequestQueue queue = Volley.newRequestQueue(this);
            //da testare questa parte
            StringRequest sRequest = new StringRequest(Request.Method.POST, "https://dummy.restapiexample.com/api/v1/employee/1",null,response -> {
                try{
                    token.setText(response.getMessage());
                }catch(Exception e){
                    e.printStackTrace();
                }
            });
        }else{
            AlertDialog alert = new AlertDialog.Builder(this)
                    .setMessage("Inserire la qualitità di rifiuti da buttare")
                    .setTitle("Inserire i rifiuti")
                    .setPositiveButton("ok",new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                        }
                    })
                    .create();
            alert.show();
        }

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
                state.setText("BT State: connected");
                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener(){
                    @Override
                    public void onMessageReceived(String receivedMessage){
                        System.out.println(receivedMessage);
                        /*if(receivedMessage.equals("ok\n") || receivedMessage.equals("timeout\n")){
                            clearSelection();
                        }*/
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {
                        token.setText("");
                        System.out.println("Message sent");
                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                TextView state = findViewById(R.id.btState);
                state.setText("BT State: not connected");
            }
        }).execute();
    }

    public void TrashASelected(View view){
        btChannel.sendMessage("A");
        btn.setEnabled(true);
    }
    public void TrashBSelected(View view){
        btChannel.sendMessage("B");
        btn.setEnabled(true);

    }
    public void TrashCSelected(View view){
        btChannel.sendMessage("C");
        btn.setEnabled(true);
    }
    private void clearSelection(){
        final RadioGroup group = findViewById(R.id.trashes);
        group.clearCheck();
    }
    public void RequestDelay(View view){
        btChannel.sendMessage("delay");
    }
}