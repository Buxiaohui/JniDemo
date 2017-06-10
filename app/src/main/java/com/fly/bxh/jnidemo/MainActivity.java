package com.fly.bxh.jnidemo;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native_mine_lib");
        System.loadLibrary("native-lib");
    }

    TextView tv, tv1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);
        tv1 = (TextView) findViewById(R.id.sample_text1);
        tv.setText(stringFromJNI());
        tv1.setText(stringFromMineJNI());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        menu.add(0, 0, 0, "test add");
        menu.add(0, 1, 1, "test int[]");
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        switch (id) {
            case R.id.action_settings:
                break;
            case 0:
                int temp = addFromMineJNI(11,12);
                tv1.setText("11+12="+temp);
                break;
            case 1:
                int[] a = {1,2,3,4,51,3};
                StringBuffer stringBufferA = new StringBuffer();
                for (int i = 0; i < a.length; i++) {
                    stringBufferA.append(a[i]).append("  ");
                }
                int[] b =  intArrayFromMineJNI(a);
                StringBuffer stringBufferB = new StringBuffer();
                if(b!= null){
                    for (int i = 0; i < b.length; i++) {
                        stringBufferB.append(b[i]).append("  ");
                    }
                }else{
                    stringBufferB.append("result is null");
                }

                tv1.setText(stringBufferA.toString()+"  ->"+ stringBufferB.toString());
                break;
        }

        return super.onOptionsItemSelected(item);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String stringFromMineJNI();

    public native int addFromMineJNI(int x, int y);

    public native int[] intArrayFromMineJNI(int[] intArray);
}
