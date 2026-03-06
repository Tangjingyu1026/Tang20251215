package com.rockmong.demo_pwm;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.rockmong.rockmong.MISC;
import com.rockmong.rockmong.IO;
import com.rockmong.rockmong.PWM;
import com.rockmong.rockmong.UsbDevice;
import com.sun.jna.Memory;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;

public class PWMActivity extends AppCompatActivity {
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

        // 初始化PWM0为1KHz，50%占空比
        ret = PWM.INSTANTCE.PWM_Init(SerialNumbers[0], 0, 1000, 500, 0, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        // PWM0开始输出
        ret = PWM.INSTANTCE.PWM_Start(SerialNumbers[0], 0, 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        // PWM0占空比设置为30%
        // 300 / 1000 * 100% = 30%
        ret = PWM.INSTANTCE.PWM_SetDuty(SerialNumbers[0], 0, 300);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

        // PWM0停止输出
        ret = PWM.INSTANTCE.PWM_Stop(SerialNumbers[0], 0);
        if (0 > ret) {
            System.out.println("Error: " + ret);
        }

    }

}
