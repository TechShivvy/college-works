// MainActivity.java

package com.example.database;

import androidx.appcompat.app.AppCompatActivity;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    SQLiteDatabase db;
    EditText name, age, course; // Assuming you have additional attributes


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        DBHelper helper = new DBHelper(this);
        db = helper.getWritableDatabase(); // Use getWritableDatabase for both reading and writing
    }

    // Insert operation
    public void insert(View v) {
        name = findViewById(R.id.age);
        age = findViewById(R.id.age);
        course = findViewById(R.id.course);

        String nametxt = name.getText().toString();
        int agetxt = Integer.parseInt(age.getText().toString()); // Assuming age is an integer
        String coursetxt = course.getText().toString();

        ContentValues cv = new ContentValues();
        cv.put("name", nametxt);
        cv.put("age", agetxt);
        cv.put("course", coursetxt);

        long x = db.insert("student", null, cv);
        if (x != -1) {
            Toast.makeText(this, "Inserted", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Insert failed", Toast.LENGTH_SHORT).show();
        }
    }

    // Read operation
    public void read(View v) {
        Cursor cursor = db.query("student", null, null, null, null, null, null);

        if (cursor.moveToFirst()) {
            do {
                String name = cursor.getString(cursor.getColumnIndex("name"));
                int age = cursor.getInt(cursor.getColumnIndex("age"));
                String course = cursor.getString(cursor.getColumnIndex("course"));

                // Do something with the data (e.g., display in TextView or log)
                // For simplicity, let's just log the data
                System.out.println("Name: " + name + ", Age: " + age + ", Course: " + course);

            } while (cursor.moveToNext());
        }

        cursor.close();
    }

    // Update operation
    public void update(View v) {
        name = findViewById(R.id.name);
        age = findViewById(R.id.age);
        course = findViewById(R.id.course);

        String nametxt = name.getText().toString();
        int agetxt = Integer.parseInt(age.getText().toString());
        String coursetxt = course.getText().toString();

        ContentValues cv = new ContentValues();
        cv.put("age", agetxt);
        cv.put("course", coursetxt);

        int rowsAffected = db.update("student", cv, "name=?", new String[]{nametxt});

        if (rowsAffected > 0) {
            Toast.makeText(this, "Updated", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Update failed", Toast.LENGTH_SHORT).show();
        }
    }

    // Delete operation
    public void delete(View v) {
        name = findViewById(R.id.name);
        String nametxt = name.getText().toString();

        int rowsAffected = db.delete("student", "name=?", new String[]{nametxt});

        if (rowsAffected > 0) {
            Toast.makeText(this, "Deleted", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Delete failed", Toast.LENGTH_SHORT).show();
        }
    }

}
