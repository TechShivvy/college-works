package com.example.file;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class MainActivity extends AppCompatActivity {
    Button read,write;
    EditText et1,et2,et3;
    TextView tv1;
    @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        et1=findViewById(R.id.et1);
        et2=findViewById(R.id.et2);
        et3=findViewById(R.id.et3);
        tv1=findViewById(R.id.tv1);
        read=findViewById(R.id.read);
        write=findViewById(R.id.write);

        read.setOnClickListener(new View.OnClickListener() {
            String data;
            @Override
            public void onClick(View view) {
                String finaldata="";
                File myfile=new File(getExternalFilesDir("/"),et1.getText().toString());
                try {
                    FileInputStream fin=new FileInputStream(myfile);
                    BufferedReader br=new BufferedReader(new InputStreamReader(fin));
                    while((data=br.readLine())!=null){
                        finaldata+=data;
                    }
                    tv1.setText(finaldata);
                    fin.close();
                    br.close();
                } catch (FileNotFoundException e) {
                    throw new RuntimeException(e);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

            }
        });
        write.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                File myfile=new File(getExternalFilesDir("/"),et2.getText().toString());
                try (FileOutputStream fout = new FileOutputStream(myfile)) {
                    fout.write(et3.getText().toString().getBytes());
                    fout.close();
                } catch (FileNotFoundException e) {
                    throw new RuntimeException(e);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

            }
        });
    }
}