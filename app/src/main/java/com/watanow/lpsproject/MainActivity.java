package com.watanow.lpsproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.watanow.lbslogicpkg.LbsLogicMain;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        LbsLogicMain nativeApi = new LbsLogicMain();
        int result = nativeApi.ndkLbsLogic(5, 10);

        int []arr ={1,2,3,4,5};

        nativeApi.ndkLbsArrayLogic(arr);

        nativeApi.ndkLbsStringLogic("Hello");

        Log.d("","result : " + result);
    }


}
