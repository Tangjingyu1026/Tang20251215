package com.rockmong.rockmong;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface UsbDevice extends Library{
	UsbDevice INSTANCE  = (UsbDevice)Native.loadLibrary("rockmong",UsbDevice.class); 
	
	int UsbDevice_Scan(int[] SerialNumbers);
}
