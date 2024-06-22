package com.example.alarm;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TimePicker;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {

    private TimePicker timePicker;
    private ToggleButton toggleButton;
    private AlarmManager alarmManager;
    private PendingIntent pendingIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        timePicker = findViewById(R.id.timePicker);
        toggleButton = findViewById(R.id.toggleButton);
        alarmManager = (AlarmManager) getSystemService(Context.ALARM_SERVICE);

        Intent alarmIntent = new Intent(this, AlarmReceiver.class);
        pendingIntent = PendingIntent.getBroadcast(this, 0, alarmIntent, 0);

        toggleButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (toggleButton.isChecked()) {
                    setAlarm();
                } else {
                    cancelAlarm();
                }
            }
        });
    }

    private void setAlarm() {
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.HOUR_OF_DAY, timePicker.getCurrentHour());
        calendar.set(Calendar.MINUTE, timePicker.getCurrentMinute());

        long triggerTime = calendar.getTimeInMillis();

        alarmManager.set(AlarmManager.RTC_WAKEUP, triggerTime, pendingIntent);

        // Show message to user in the activity UI
        showToast("Alarm set for " + calendar.getTime());

        // Play the alarm ringtone (you may want to customize this part)
        playAlarmRingtone();
    }

    private void cancelAlarm() {
        alarmManager.cancel(pendingIntent);

        // Show message to user in the activity UI
        showToast("Alarm canceled");

        // Stop playing the alarm ringtone (if necessary)
        // Stop any ongoing notification (if necessary)
    }

    private void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    private void playAlarmRingtone() {
        // Implement the logic to play the alarm ringtone
    }
}