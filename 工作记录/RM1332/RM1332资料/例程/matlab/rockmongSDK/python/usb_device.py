#-*- coding: utf-8 -*-
from ctypes import *
import platform
from librockmong import *

#扫描USB设备
#返回值如果大于0，代表获取到设备的个数。如果等于0，代表未插入设备。如果小于0，代表发生错误
def UsbDevice_Scan(SerialNumbers):
    return librockmong.UsbDevice_Scan(SerialNumbers)
	
def UsbDevice_Open(SerialNumber):
    return librockmong.UsbDevice_Open(SerialNumber)
	
def UsbDevice_Close(SerialNumber):
    return librockmong.UsbDevice_Close(SerialNumber)