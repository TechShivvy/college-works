package com.example.webview;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private WebView webView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        webView = (WebView) findViewById(R.id.webView);

        webView.setWebViewClient(new WebViewClient());

        //load data from here
//        webView.loadData("<h1>Hello</h1>","text/html","UTF-8");

        //load url
//         webView.loadUrl("https://pastebin.com/TtgT0Uka");

        //load static html ----- create by right clicking app->new->folder>assets->put file there.
        webView.loadUrl("file:///android_asset/index.html");

        //js shiz
//        WebSettings ws = webView.getSettings();
//        ws.setJavaScriptEnabled(true);
    }

    //back button logic
    @Override
    public void onBackPressed() {
        if(webView!=null &&  webView.canGoBack()){
            webView.goBack();
            return;
        }
        super.onBackPressed();
    }

    //get url from user and loadUrl
    public void handleClick(View v)
    {
        webView.loadUrl("https://"+((TextView)findViewById(R.id.url)).getText().toString());
    }
}