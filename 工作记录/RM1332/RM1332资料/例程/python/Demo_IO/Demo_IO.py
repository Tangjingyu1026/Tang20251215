#-*- coding: utf-8 -*-
from ctypes import *
import os
import sys
public_path = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + "/../public")
sys.path.append(public_path)
from librockmong import *
from device import *
from gpio import *
from time import sleep

if __name__ == '__main__':
    SerialNumbers = (c_int * 20)()
    sn = 0
    # Scan device
    ret = Device_Scan(byref(SerialNumbers))
    if (0 > ret):
        print("Error: %d"%ret)
        exit()
    elif(ret == 0):
        print("No device!")
        exit()
    else:
        for i in range(ret):
            print("Dev%d SN: %d"%(i, SerialNumbers[i]))
    
    sn = SerialNumbers[0]#选择设备0

    # 打开设备
    ret = Device_Open(sn)
    if (0 > ret):
        print("error: %d"%ret)
        exit()

    #初始化P0为输出模式
    ret = IO_InitPin(sn, 0, 1, 0)
    if (0 > ret):
        print("error: %d"%ret)
    
    #控制P0输出高电平
    ret = IO_WritePin(sn, 0, 1)
    if (0 > ret):
        print("error: %d"%ret)
    
    #控制P0输出低电平
    ret = IO_WritePin(sn, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)

    #初始化P0为输入模式
    ret = IO_InitPin(sn, 0, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)
        
    #读取P0电平状态
    PinState = (c_int)()
    ret = IO_ReadPin(sn, 0, byref(PinState))
    if (0 > ret):
        print("error: %d"%ret)
    print("Pin state: %d"%PinState.value)

    # 关闭设备
    ret = Device_Close(sn)
    if (0 > ret):
        print("error: %d"%ret)

    
