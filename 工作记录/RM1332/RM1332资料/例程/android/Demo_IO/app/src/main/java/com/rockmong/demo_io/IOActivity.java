package com.rockmong.demo_io;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rockmong.rockmong.MISC;
import com.rockmong.rockmong.IO;
import com.rockmong.rockmong.UsbDevice;
import com.sun.jna.Memory;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;

public class IOActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        int ret;
        int[] SerialNumbers = new int[16];
        ret = UsbDevice.INSTANTCE.UsbDevice_Scan(SerialNumbers);
        if (0 > ret) {
            System.out.println("Error: " + ret);
            return;
        }
        else if (0 == ret){
            System.out.println("No Device!");
            return;
        }
        else{
            for (int i = 0; i < ret; i++){
                System.out.println("Dev" + i + " SN: " + SerialNumbers[i]);
            }
        }

        //初始化P0为输出模式
        ret = IO.INSTANTCE.IO_InitPin(SerialNumbers[0], 0, 1, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        //控制P0输出高电平
        ret = IO.INSTANTCE.IO_WritePin(SerialNumbers[0], 0, 1);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        //控制P0输出低电平
        ret = IO.INSTANTCE.IO_WritePin(SerialNumbers[0], 0, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        //初始化P0为输入模式
        ret = IO.INSTANTCE.IO_InitPin(SerialNumbers[0], 0, 0, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        //读取P0输入状态
        IntByReference PinState = new IntByReference();
        ret = IO.INSTANTCE.IO_ReadPin(SerialNumbers[0], 0, PinState);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }
        System.out.println("PinState: " + PinState.getValue());
    }

}
