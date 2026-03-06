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
    io_count = 16
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
    
    sn = SerialNumbers[0]# 选择设备0

    # 打开设备
    ret = Device_Open(sn)
    if (0 > ret):
        print("error: %d"%ret)
        exit()

    IO_InitMulti_TxStrut = (IO_InitMultiPin_TxStruct_t*io_count)()
    IO_InitMulti_RxStruct = (IO_InitMultiPin_RxStruct_t*io_count)()
    
    for i in range(io_count):
        IO_InitMulti_TxStrut[i].Pin = i
        IO_InitMulti_TxStrut[i].Mode = 1
        IO_InitMulti_TxStrut[i].Pull = 0
    # 初始化所有IO口为输出模式
    ret = IO_InitMultiPin(sn, IO_InitMulti_TxStrut, IO_InitMulti_RxStruct, io_count)
    if (0 > ret):
        for i in range(io_count):
            print("error: %d"%IO_InitMulti_RxStruct[i].Ret)
           
    IO_WriteMulti_TxStruct = (IO_WriteMultiPin_TxStruct_t*io_count)()
    IO_WriteMulti_RxStruct = (IO_WriteMultiPin_RxStruct_t*io_count)()
     
    for i in range(io_count):
        IO_WriteMulti_TxStruct[i].Pin = i
        IO_WriteMulti_TxStruct[i].PinState = 1
    # 控制所有引脚输出高电平
    ret = IO_WriteMultiPin(sn, IO_WriteMulti_TxStruct, IO_WriteMulti_RxStruct, io_count)
    if (0 > ret):
        for i in range(io_count):
            print("error: %d"%IO_WriteMulti_RxStruct[i].Ret)

    for i in range(io_count):
        IO_WriteMulti_TxStruct[i].Pin = i
        IO_WriteMulti_TxStruct[i].PinState = 0
    # 控制所有引脚输出低电平
    ret = IO_WriteMultiPin(sn, IO_WriteMulti_TxStruct, IO_WriteMulti_RxStruct, io_count)
    if (0 > ret):
        for i in range(io_count):
            print("error: %d"%IO_WriteMulti_RxStruct[i].Ret)
    
    for i in range(io_count):
        IO_InitMulti_TxStrut[i].Pin = i
        IO_InitMulti_TxStrut[i].Mode = 0
        IO_InitMulti_TxStrut[i].Pull = 0
    # 初始化所有IO口为输入模式
    ret = IO_InitMultiPin(sn, IO_InitMulti_TxStrut, IO_InitMulti_RxStruct, io_count)
    if (0 > ret):
        for i in range(io_count):
            print("error: %d"%IO_InitMulti_RxStruct[i].Ret)

    IO_ReadMulti_TxStruct = (IO_ReadMultiPin_TxStruct_t*io_count)()
    IO_ReadMulti_RxStruct = (IO_ReadMultiPin_RxStruct_t*io_count)()
     
    for i in range(io_count):
        IO_ReadMulti_TxStruct[i].Pin = i
    # 读取所有IO口状态
    ret = IO_ReadMultiPin(sn, IO_ReadMulti_TxStruct, IO_ReadMulti_RxStruct, io_count)
    if (0 > ret):
        for i in range(io_count):
            print("error: %d"%IO_ReadMulti_RxStruct[i].Ret)
    for i in range(io_count):
        print("P%d: %d\t"%(i,IO_ReadMulti_RxStruct[i].PinState), end="")
    print("")

    # 关闭设备
    ret = Device_Close(sn)
    if (0 > ret):
        print("error: %d"%ret)

    
