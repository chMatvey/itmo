package ru.chudakov.timerapp_chudakov;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import java.text.MessageFormat;

public class MainActivity extends AppCompatActivity {

    private int seconds = 0;

    private boolean running = false;

    private String timerValue = "00:00:00";

    private TextView timerText;

    private Handler timerHandler = new Handler();

    private Runnable runTimer = new Runnable() {
        @Override
        public void run() {
            if (running) {
                seconds++;

                int minutes = seconds / 60;
                int hours = minutes / 60;
                minutes %= 60;

                timerValue = MessageFormat.format("{0}:{1}:{2}", toFormat(hours), toFormat(minutes), toFormat(seconds % 60));

                timerText.setText(timerValue);
            }

            timerHandler.postDelayed(this, 1000);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        init();
    }

    @Override
    protected void onPause() {
        super.onPause();

        timerHandler.removeCallbacks(runTimer);
    }

    @Override
    protected void onResume() {
        super.onResume();

        timerText.setText(timerValue);

        timerHandler.postDelayed(runTimer, 1000);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

        outState.putInt("seconds", seconds);
        outState.putBoolean("running", running);
        outState.putString("timerValue", timerValue);
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        running = savedInstanceState.getBoolean("running");
        seconds = savedInstanceState.getInt("seconds");
        timerValue = savedInstanceState.getString("timerValue");
    }

    private void init() {
        timerText = findViewById(R.id.time_text);

        Button startButton = findViewById(R.id.start_button);
        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                running = true;
            }
        });

        Button stopButton = findViewById(R.id.stop_button);
        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                running = false;
            }
        });

        Button resetButton = findViewById(R.id.reset_button);
        resetButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                running = false;
                seconds = 0;
                timerValue = "00:00:00";

                timerText.setText(R.string.timer_default);
            }
        });
    }

    private String toFormat(int time) {
        return String.format("%2s", time).replace(' ', '0');
    }
}
