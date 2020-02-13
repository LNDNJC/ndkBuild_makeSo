package com.watanow.lpsproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import com.watanow.lbslogicpkg.LbsLogicMain;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    LbsLogicMain nativeApi;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        nativeApi = new LbsLogicMain();
        int result = nativeApi.ndkLbsLogic(5, 10);

        int []arr ={1,2,3,4,5};

        nativeApi.ndkLbsIntArrayLogic(arr);

        nativeApi.ndkLbsStringLogic("Hello");

        nativeApi.getNumString("Hello", 10);

        int ret = -1;
        ret = nativeApi.startThread();

        Log.d("","result : " + result);
    }

    @Override
    protected void onStop()
    {
        super.onStop();
        int ret = -1;
        ret = nativeApi.endThread();
        Log.e("Java", "endThread : " +ret );
    }


}
