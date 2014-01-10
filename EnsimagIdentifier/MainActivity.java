package com.example.ensimagidentifiers;

import java.net.URI;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;
import android.net.Uri;
import android.net.wifi.WifiManager;
public class MainActivity extends Activity {
	
	public String getMACAddress() {
		return ((WifiManager) this.getSystemService(Context.WIFI_SERVICE)).getConnectionInfo().getMacAddress();
	}

	public static String HTTPGet(URI uri) {
        String responseBody = "";
		try {
            HttpGet get = new HttpGet();
            get.setURI(uri);
            DefaultHttpClient httpClient = new DefaultHttpClient();
            HttpResponse response = httpClient.execute(get);
            int responseCode = response.getStatusLine().getStatusCode();
            switch (responseCode)
            {
            	case 200:
                    HttpEntity entity = response.getEntity();
                    if(entity != null)
                    {
                    	responseBody = EntityUtils.toString(entity);     
                    }
                    break;
            
            }
        } catch (Exception e) {
            Log.e("[GET REQUEST]", e.getMessage());
        }
		return responseBody;
}

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    	TextView textView = (TextView)findViewById(R.id.macaddress);
    	String macAddress = getMACAddress();
        String uriToAccess = "http://192.168.42.1:1000/scantag?mac=" + macAddress;
        URI uri;
		try {
			uri = new URI(uriToAccess);
	        String response = HTTPGet(uri);
	        //response = "https://www.google.com/calendar/embed?src=cdobi02tvc96abm42o70egikr4%40group.calendar.google.com&ctz=Europe/Paris";
	        if (!response.equals("OK")) {
	        	Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(response));
	        	startActivity(browserIntent);
				finish();
	        } else {
				textView.setText("Professeur identifié. Vous pouvez fermer l'application.");
	        }
		} catch (Exception e) {
			e.printStackTrace();
			textView.setText(e.toString());
		}
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
