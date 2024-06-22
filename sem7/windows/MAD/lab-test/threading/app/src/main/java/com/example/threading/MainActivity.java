package com.example.threading;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private TextView colorTextView, bannerTextView, counterTextView;
    private Button startButton, stopButton;

    private volatile boolean stopThreads = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        colorTextView = findViewById(R.id.colorTextView);
        bannerTextView = findViewById(R.id.bannerTextView);
        counterTextView = findViewById(R.id.counterTextView);

        startButton = findViewById(R.id.startButton);
        stopButton = findViewById(R.id.stopButton);

        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopThreads = false;
                startColorThread();
                startBannerThread();
                startCounterThread();
            }
        });

        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopThreads = true;
            }
        });
    }

    private void startColorThread() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (!stopThreads) {
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            changeTextColor();
                        }
                    });
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    private void startBannerThread() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (!stopThreads) {
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            moveBanner();
                        }
                    });
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    private void startCounterThread() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i <= 1000 && !stopThreads; i++) {
                    final int finalI = i;
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            updateCounter(finalI);
                        }
                    });
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    private void changeTextColor() {
        // Change text color logic
        // For simplicity, let's toggle between two colors
        colorTextView.setTextColor(colorTextView.getCurrentTextColor() == getResources().getColor(R.color.white) ?
                getResources().getColor(R.color.black) :
                getResources().getColor(R.color.white));
    }

    private void moveBanner() {
        // Move banner logic
        // For simplicity, let's scroll the text
        String currentText = bannerTextView.getText().toString();
        String newText = currentText.substring(1) + currentText.charAt(0);
        bannerTextView.setText(newText);
    }

    private void updateCounter(int count) {
        counterTextView.setText(String.valueOf(count));
    }
}
