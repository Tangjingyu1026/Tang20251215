package com.rockmong.demo_pwm;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.rockmong.rockmong.UsbDevice;
import com.sun.jna.Pointer;

public class UsbManagerActivity {

    private Context context;
    private UsbManager usbManager;
    private static final String ACTION_USB_PERMISSION ="com.rockmong.USB_PERMISSION";

    public UsbManagerActivity(Context context)
    {
        this.context = context;

        //注册USB插拔检测服务
        IntentFilter filter = new IntentFilter();
        filter.addAction(UsbManager.ACTION_USB_DEVICE_DETACHED);
        filter.addAction(UsbManager.ACTION_USB_DEVICE_ATTACHED);
        filter.addAction(ACTION_USB_PERMISSION);
        filter.setPriority(Integer.MAX_VALUE); //设置级别
        UsbReceiver usbReceiver = new UsbReceiver();
        context.registerReceiver(usbReceiver,filter);

        Scan();
    }

    public int Scan()
    {
        int ret = 0;

        UsbDevice.INSTANTCE.UsbDevice_Clear();

        usbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
        HashMap<String, android.hardware.usb.UsbDevice> deviceList = usbManager.getDeviceList();
        for (android.hardware.usb.UsbDevice usbDevice : deviceList.values()) {
            if(UsbDevice.INSTANTCE.UsbDevice_GetVid() == usbDevice.getVendorId() && UsbDevice.INSTANTCE.UsbDevice_GetPid() == usbDevice.getProductId()){
                if(!usbManager.hasPermission(usbDevice)) {
                    PendingIntent mPermissionIntent = PendingIntent.getBroadcast(context, 0, new Intent(ACTION_USB_PERMISSION), 0);
                    usbManager.requestPermission(usbDevice, mPermissionIntent);
                }
                else {
                    UsbDeviceConnection usbDeviceConnection = usbManager.openDevice(usbDevice);
                    int fileDescriptor = usbDeviceConnection.getFileDescriptor();

                    ret = UsbDevice.INSTANTCE.UsbDevice_SetFd(fileDescriptor);
                    if (0 > ret) {
                        System.out.println("Error: " + ret);
                    }
                }
            }
        }

        return  ret;
    }

    //定义USB的插拔广播接收器
    private class UsbReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals(UsbManager.ACTION_USB_DEVICE_DETACHED)) {
                Toast.makeText(context, "Device Detached", Toast.LENGTH_SHORT).show();
                Scan();
            }else if (intent.getAction().equals(UsbManager.ACTION_USB_DEVICE_ATTACHED)){
                Toast.makeText(context, "Device Attached", Toast.LENGTH_SHORT).show();
                android.hardware.usb.UsbDevice usbDevice = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
                if(!usbManager.hasPermission(usbDevice)){
                    PendingIntent pendingIntent = PendingIntent.getBroadcast(context, 0, new Intent(ACTION_USB_PERMISSION), 0);
                    usbManager.requestPermission(usbDevice, pendingIntent);
                }
            }else if(intent.getAction().equals(ACTION_USB_PERMISSION)){
                //UsbDevice usbDevice = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
                if(intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED,false)){
                    System.out.println("Permission ok");
                    Scan();
                }else{
                    System.out.println("No permission");
                }
            }
        }
    }

}
