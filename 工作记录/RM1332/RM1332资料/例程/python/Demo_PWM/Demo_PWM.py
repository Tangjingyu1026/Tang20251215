#-*- coding: utf-8 -*-
from ctypes import *
import os
import sys
public_path = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + "/../public")
sys.path.append(public_path)
from librockmong import *
from device import *
from gpio import *
from pwm import *
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
    
    sn = SerialNumbers[0]   # 选择设备0

    # 打开设备
    ret = Device_Open(sn)
    if (0 > ret):
        print("error: %d"%ret)
        exit()

    # 初始化PWM通道0
    # 频率=1000Hz, 占空比=50%, 相位=0, 极性=0
    ret = PWM_Init(sn, 0, 1000, 500, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)
    
    # 控制PWM输出波形
    ret = PWM_Start(sn, 0, 0)
    if (0 > ret):
        print("error: %d"%ret)
    
    # 动态调节占空比到80%
    ret = PWM_SetDuty(sn, 0, 800)
    if (0 > ret):
        print("error: %d"%ret)

    # 控制PWM停止输出
    ret = PWM_Stop(sn, 0)
    if (0 > ret):
        print("error: %d"%ret)

    # 关闭设备
    ret = Device_Close(sn)
    if (0 > ret):
        print("error: %d"%ret)



    
