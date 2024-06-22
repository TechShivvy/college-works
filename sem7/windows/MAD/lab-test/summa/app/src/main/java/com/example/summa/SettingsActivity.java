package com.example.summa;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class SettingsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        Intent i = getIntent();
        String msg = i.getStringExtra("COOL");
        if(msg!=null)
            ((TextView)findViewById(R.id.textbox2)).setText(msg);
    }
}