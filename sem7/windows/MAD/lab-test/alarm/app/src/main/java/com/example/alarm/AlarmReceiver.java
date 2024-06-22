package com.example.alarm;

import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

public class AlarmReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        // Show Android notification message
        showNotification(context, "Alarm Triggered");

        // You can add more actions or notifications here
    }

    private void showNotification(Context context, String message) {
        // Implement the logic to create and show an Android notification
        // You may use NotificationCompat.Builder for compatibility with different Android versions
    }
}