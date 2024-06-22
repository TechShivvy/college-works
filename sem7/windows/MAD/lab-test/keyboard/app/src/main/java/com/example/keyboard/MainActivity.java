package com.example.keyboard;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.w3c.dom.Text;

public class MainActivity extends AppCompatActivity {

    final char[] row1Alpha = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
    final char[] row2Alpha = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
    final char[] row3Alpha = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    final char[] row1Num = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    final char[] row2Num = {'@', '#', '_', '&', '-', '+', '(', ')', '/'};
    final char[] row3Num = {'*', '"', '\'', ':', ';', '!', '?'};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initialiseKeyboard();
    }

    protected void initialiseKeyboard(){
        LinearLayout row1 = findViewById(R.id.row1);
        LinearLayout row2 = findViewById(R.id.row2);
        LinearLayout row3 = findViewById(R.id.row3);

        for(int i=0;i<row1.getChildCount();i++){
            View child = row1.getChildAt(i);
            TextView btn = (TextView) child;

            btn.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    TextView output = findViewById(R.id.textViewOutput);
                    output.append(btn.getText().toString());
                }
            });
        }

        for(int i=0;i<row2.getChildCount();i++){
            View child = row2.getChildAt(i);
            TextView btn = (TextView) child;

            btn.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    TextView output = findViewById(R.id.textViewOutput);
                    output.append(btn.getText().toString());
                }
            });
        }

        for(int i=1;i<row3.getChildCount()-1;i++){
            View child = row3.getChildAt(i);
            TextView btn = (TextView) child;

            btn.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    TextView output = findViewById(R.id.textViewOutput);
                    output.append(btn.getText().toString());
                }
            });
        }

        // Setting Caps and backspace
        TextView caps = (TextView)row3.getChildAt(0);
        caps.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Toggle caps
                TextView valView = (TextView)row1.getChildAt(0);
                String val = valView.getText().toString();
                if(!Character.isAlphabetic(val.charAt(0))){
                    return;
                }
                if(Character.isLowerCase(val.charAt(0))){
                    for(int i=0;i<row1.getChildCount();i++){
                        TextView btn = (TextView) row1.getChildAt(i);
                        btn.setText(String.valueOf(Character.toUpperCase(row1Alpha[i])));
                    }
                    for(int i=0;i<row2.getChildCount();i++){
                        TextView btn = (TextView) row2.getChildAt(i);
                        btn.setText(String.valueOf(Character.toUpperCase(row2Alpha[i])));
                    }
                    for(int i=1;i<row3.getChildCount()-1;i++){
                        TextView btn = (TextView) row3.getChildAt(i);
                        btn.setText(String.valueOf(Character.toUpperCase(row3Alpha[i-1])));
                    }
                }
                else {
                    for(int i=0;i<row1.getChildCount();i++){
                        TextView btn = (TextView) row1.getChildAt(i);
                        btn.setText(String.valueOf(row1Alpha[i]));
                    }
                    for(int i=0;i<row2.getChildCount();i++){
                        TextView btn = (TextView) row2.getChildAt(i);
                        btn.setText(String.valueOf(row2Alpha[i]));
                    }
                    for(int i=1;i<row3.getChildCount()-1;i++){
                        TextView btn = (TextView) row3.getChildAt(i);
                        btn.setText(String.valueOf(row3Alpha[i-1]));
                    }
                }
            }
        });
        // backspace
        TextView backspace = (TextView)row3.getChildAt(row3.getChildCount()-1);
        backspace.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                TextView output = findViewById(R.id.textViewOutput);
                if(output.getText().length() >= 1){
                    output.setText(output.getText().subSequence(0,output.getText().length()-1));
                }
            }
        });

        // Enter button
        TextView enter = (TextView) findViewById(R.id.Enter);
        enter.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                TextView output = findViewById(R.id.textViewOutput);
                if(output.getText().length() >= 1){
                    output.append("\n");
                }
            }
        });
        // Space,
        TextView space = (TextView) findViewById(R.id.Space);
        space.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                TextView output = findViewById(R.id.textViewOutput);
                if(output.getText().length() >= 1){
                    output.append(" ");
                }
            }
        });
        // Set Number, Alphabet,
        TextView toNum = (TextView) findViewById(R.id.Num);
        toNum.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                for(int i=0;i<row1.getChildCount();i++){
                    TextView btn = (TextView) row1.getChildAt(i);
                    btn.setText(String.valueOf(row1Num[i]));
                }
                for(int i=0;i<row2.getChildCount();i++){
                    TextView btn = (TextView) row2.getChildAt(i);
                    btn.setText(String.valueOf(row2Num[i]));
                }
                for(int i=1;i<row3.getChildCount()-1;i++){
                    TextView btn = (TextView) row3.getChildAt(i);
                    btn.setText(String.valueOf(row3Num[i-1]));
                }
            }
        });

        TextView toAlpha = (TextView) findViewById(R.id.Alpha);
        toAlpha.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                for(int i=0;i<row1.getChildCount();i++){
                    TextView btn = (TextView) row1.getChildAt(i);
                    btn.setText(String.valueOf(row1Alpha[i]));
                }
                for(int i=0;i<row2.getChildCount();i++){
                    TextView btn = (TextView) row2.getChildAt(i);
                    btn.setText(String.valueOf(row2Alpha[i]));
                }
                for(int i=1;i<row3.getChildCount()-1;i++){
                    TextView btn = (TextView) row3.getChildAt(i);
                    btn.setText(String.valueOf(row3Alpha[i-1]));
                }
            }
        });
    }
}