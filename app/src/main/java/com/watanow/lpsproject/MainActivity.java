package com.watanow.lpsproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.watanow.lbslogicpkg.LbsLogicMain;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        LbsLogicMain nativeApi = new LbsLogicMain();
        int result = nativeApi.ndkLbsLogic(5, 10);

        Log.d("","result : " + result);
    }
}
