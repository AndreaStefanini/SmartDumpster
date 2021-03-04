package com.example.smartdumpster;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
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

import java.util.HashSet;
import java.util.Set;

import static androidx.core.app.ActivityCompat.startActivityForResult;

/**
 * TODO:
 *  request to turn on wifi DONE
 *  request to turn on bt DONE
 *  add bluetooth device to pair list
 *  use a BT library to manage the exchange of information
 *
 */
public class MainActivity extends AppCompatActivity {
    private TextView token;
    private String Token;
    private Button btn;
    private BluetoothAdapter bltAdapt;
    private String BT_TARGET_NAME = "SmartDumpster";
    private Set<BluetoothDevice> newBluetoothDevice= new HashSet<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        bltAdapt = BluetoothAdapter.getDefaultAdapter();
        registerReceiver(receiver, new IntentFilter(BluetoothDevice.ACTION_FOUND));


    }
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if(BluetoothDevice.ACTION_FOUND.equals(intent.getAction())){
                BluetoothDevice device=intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                newBluetoothDevice.add(device);
            }
        }
    };
    public void onStart() {
        super.onStart();
        checkBluetooth();
        checkWifi();
        if (bltAdapt.startDiscovery()){
            System.out.println("iniziata la discovery");
        }else{
            System.out.println("Non iniziata la discovery");
        }

        token = (TextView) findViewById(R.id.token);
        SetUpBTConnection();
    }
    public void onStop() {
        super.onStop();
        bltAdapt.cancelDiscovery();
        unregisterReceiver(receiver);
    }
    public void GetToken(View view){

        RequestQueue requestQ = Volley.newRequestQueue(this);
        JsonObjectRequest objectRequest = new JsonObjectRequest(Request.Method.GET,"https://dummy.restapiexample.com/api/v1/employee/1", null,
                response -> {
                    try {
                        Token  = (String) response.getJSONObject("data").get("employee_name");
                        token.setText(Token.toString());

                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                },
                error -> token.setText(error.getMessage()));
        requestQ.add(objectRequest);
        //StringRequest stringQ = new StringRequest(Request.Method.GET, "http://dummy.restapiexample.com/api/v1/employee/1",  response -> token.setText(response), error -> token.setText("There was an error during comunication with the server"));
        //System.out.println(Token);

        btn = (Button) findViewById(R.id.throw_garbage);
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
    private void checkBluetooth(){
        if(bltAdapt== null){
            AlertDialog dialog = new AlertDialog.Builder(this)
                    .setTitle("Bluetooth is missing")
                    .setMessage("This device seems not having the bluetooth, it might be a bug, in that case reboot the system, otherwise you need to get a bluetooth adapter.")
                    .setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            dialog.dismiss();
                            System.exit(0);
                        }
                    })
                    .create();
        }else if(!bltAdapt.isEnabled()){
            Intent blueOn = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(blueOn, 1);
        }

    }
    private void SetUpBTConnection(){
        BluetoothDevice targetDevice = null;
        Set<BluetoothDevice> pairedList = bltAdapt.getBondedDevices();
        if(pairedList.size()>0){
            for (BluetoothDevice device : pairedList){
                if(device.getName() == BT_TARGET_NAME){
                    targetDevice = device;

                }
            }
        }
        if(targetDevice!=null){
            System.out.print(targetDevice.getName());
        }else{
            //System.out.println("non trovato");
            if(newBluetoothDevice!=null){
                token.setText("Dispositivo trovato");
                for(BluetoothDevice device : newBluetoothDevice )
                        token.setText(device.getName().toString());

            }else{
                System.out.println("Dispositivo non trovato");
            }
        }
    }
}