#-*- coding: utf-8 -*-
from ctypes import *
import platform
from librockmong import *

# 扫描设备
# 返回值如果大于0，代表获取到设备的个数。如果等于0，代表未插入设备。如果小于0，代表发生错误
def Device_Scan(SerialNumbers):
    return librockmong.Device_Scan(SerialNumbers)
	
def Device_Open(SerialNumber):
    return librockmong.Device_Open(SerialNumber)
	
def Device_Close(SerialNumber):
    return librockmong.Device_Close(SerialNumber)

def Device_GetType(SerialNumber, Type):
    return librockmong.Device_GetType(SerialNumber, Type)

def Device_GetIP(SerialNumber, IP):
    return librockmong.Device_GetIP(SerialNumber, IP)