package com.example.summa;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("FRontPage");
        Log.d("success","working");
    }

    public void disable(View v)
    {
//        v.setEnabled(false);
//        Button button = (Button) v;
//        button.setText("Disabled");

        View myView = findViewById(R.id.button);
        myView.setEnabled(false);
        Button button = (Button) myView;
        button.setText("Disabled");

        Log.d("shivi","button disabled");
    }
    public void handleText(View v)
    {
        TextView t = findViewById(R.id.input);
        String input = t.getText().toString();
        ((TextView)findViewById(R.id.textbox)).setText(input);
        Log.d("info",input);
        Toast.makeText(this,input,Toast.LENGTH_LONG).show();

    }

    public void launchSettings(View v)
    {
        Intent i = new Intent(this,SettingsActivity.class);
//        i.putExtra("COOL","COOOOOOOLD");
        i.putExtra("COOL",((EditText)findViewById(R.id.input)).getText().toString());
        startActivity(i);
    }
}