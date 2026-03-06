#-*- coding: utf-8 -*-
from ctypes import *
import os
import sys
public_path = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + "/../public")
sys.path.append(public_path)
from librockmong import *
from device import *
from counter import *
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

    #初始化Counter0
    ret = Counter_Init(sn, 0, 0, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)

    #初始化Counter1
    ret = Counter_Init(sn, 1, 0, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)

    #Counter0计数清零
    ret = Counter_Write(sn, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)

    #Counter1计数清零
    ret = Counter_Write(sn, 1, 0)
    if (0 > ret):
        print("error: %d"%ret)

    #Counter0开始计数
    ret = Counter_Start(sn, 0)
    if (0 > ret):
        print("error: %d"%ret)

    #Counter1开始计数
    ret = Counter_Start(sn, 1)
    if (0 > ret):
        print("error: %d"%ret)
    
    while(True):
        #读取Counter0计数值
        cnt0 = (c_int)()
        ret = Counter_Read(sn, 0, byref(cnt0))
        if (0 > ret):
            print("error: %d"%ret)
        print("cnt0: %d"%cnt0.value)
        #读取Counter1计数值
        cnt1 = (c_int)()
        ret = Counter_Read(sn, 1, byref(cnt1))
        if (0 > ret):
            print("error: %d"%ret)
        print("cnt1: %d"%cnt1.value)

        if (cnt0.value >= 10):
            #Counter0计数清零
            ret = Counter_Write(sn, 0, 0)
            if (0 > ret):
                print("error: %d"%ret)

        if (cnt1.value >= 100):            
            #Counter0停止计数
            ret = Counter_Stop(sn, 0)
            if (0 > ret):
                print("error: %d"%ret)
            #Counter1停止计数
            ret = Counter_Stop(sn, 1)
            if (0 > ret):
                print("error: %d"%ret)
            break

        sleep(1)

    # 关闭设备
    ret = Device_Close(sn)
    if (0 > ret):
        print("error: %d"%ret)

    
