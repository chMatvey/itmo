package ru.chudakov.intentapp_chudakov;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.util.List;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    private Intent callIntent;

    private Intent mapIntent;

    private Intent webIntent;

    private Intent mailIntent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        init();
    }

    private void init() {
        callIntent = new Intent(Intent.ACTION_DIAL, Uri.parse("tel: +79811701111"));

        mapIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(String.format(Locale.US, "geo:%.8f,%.8f", 59.957514f, 30.308279f)));

        webIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.ifmo.ru/ru/"));

        mailIntent = new Intent(Intent.ACTION_SENDTO, Uri.parse("mailto:"))
                .putExtra(Intent.EXTRA_EMAIL, new String[]{"matvey.chudakov@yandex.ru"})
                .putExtra(Intent.EXTRA_SUBJECT, "Email subject")
                .putExtra(Intent.EXTRA_TEXT, "Email message text");


        Button callButton = findViewById(R.id.button_call);
        callButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isIntentSafe(callIntent)) {
                    startActivity(callIntent);
                } else {
                    Toast.makeText(getApplicationContext(), "Your phone have no app can dial",
                            Toast.LENGTH_SHORT).show();
                }
            }
        });

        Button mapButton = findViewById(R.id.button_map);
        mapButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isIntentSafe(mapIntent)) {
                    startActivity(mapIntent);
                } else {
                    Toast.makeText(getApplicationContext(), "Your phone have no map app",
                            Toast.LENGTH_SHORT).show();
                }
            }
        });

        Button webButton = findViewById(R.id.button_web);
        webButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isIntentSafe(webIntent)) {
                    startActivity(webIntent);
                } else {
                    Toast.makeText(getApplicationContext(), "Your phone have no app can open web page",
                            Toast.LENGTH_SHORT).show();
                }
            }
        });

        Button mailButton = findViewById(R.id.button_mail);
        mailButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (isIntentSafe(mailIntent)) {
                    startActivity(mailIntent);
                } else {
                    Toast.makeText(getApplicationContext(), "Your phone have no app can send mail",
                            Toast.LENGTH_SHORT).show();
                }
            }
        });
    }

    private boolean isIntentSafe(Intent intent) {
        PackageManager packageManager = getPackageManager();
        List<ResolveInfo> activities = packageManager.queryIntentActivities(intent, 0);
        return activities.size() > 0;
    }

}
