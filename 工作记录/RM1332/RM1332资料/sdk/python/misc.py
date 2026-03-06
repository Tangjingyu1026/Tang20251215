#-*- coding: utf-8 -*-
from ctypes import *
import platform
from librockmong import *

#获取设备固件版本
#SerialNumber：设备SN
#Version：返回的版本字符串
#返回值： 小于0，异常。 等于0，正常
def MISC_GetFwVersion(SerialNumber, Version):
    return librockmong.MISC_GetFwVersion(SerialNumber, Version)

#获取设备型号
#SerialNumber：设备SN
#Model：返回的型号字符串
#返回值： 小于0，异常。 等于0，正常
def MISC_GetModel(SerialNumber, Model):
    return librockmong.MISC_GetModel(SerialNumber, Model)
	
#获取设备型号
#SerialNumber：设备SN
#Version：返回的版本字符串
#返回值： 小于0，异常。 等于0，正常
def MISC_GetLibraryVersion(Version):
    return librockmong.MISC_GetLibraryVersion(Version)
	
def MISC_SetSn(SerialNumber, NewSerialNumber):
    return librockmong.MISC_SetSn(SerialNumber, NewSerialNumber)
	
def MISC_GetData(SerialNumber, Data, Length):
    return librockmong.MISC_SetSn(SerialNumber, Data, Length)

	