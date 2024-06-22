package com.example.db;

import androidx.appcompat.app.AppCompatActivity;

import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private DBHelper helper = new DBHelper(this);
    private EditText name;
    private EditText age;
    private EditText course;

    private Button submit;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        name=findViewById(R.id.name);
        age=findViewById(R.id.age);
        course=findViewById(R.id.course);
        submit=findViewById(R.id.submitButton);

        submit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Toast.makeText(MainActivity.this, helper.addUsers(name.getText().toString(),Integer.parseInt(age.getText().toString()),course.getText().toString()), Toast.LENGTH_SHORT).show();

                Cursor cursor = helper.readUsers();
                if(cursor.moveToFirst())
                {
                    do {
                        System.out.println("Name: "+cursor.getString(0));
                        System.out.println("Age: "+cursor.getString(1));
                        System.out.println("Course: "+cursor.getString(2));
                    }while(cursor.moveToNext());
                }


            }
        });
    }
}