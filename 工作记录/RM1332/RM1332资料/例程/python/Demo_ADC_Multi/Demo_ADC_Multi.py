#-*- coding: utf-8 -*-
from ctypes import *
import os
import sys
public_path = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + "/../public")
sys.path.append(public_path)
from librockmong import *
from device import *
from gpio import *
from adc import *
from time import sleep

if __name__ == '__main__':
    SerialNumbers = (c_int * 20)()
    sn = 0
    adc_num = 8
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

    #初始化ADC0~7
    ADC_Init_TxStruct = (ADC_Init_TxStruct_t*adc_num)()
    ADC_Init_RxStruct = (ADC_Init_RxStruct_t*adc_num)()
    for i in range(adc_num):
        ADC_Init_TxStruct[i].Channel = i
        ADC_Init_TxStruct[i].SampleRateHz = 0
    ret = ADC_InitMulti(sn, ADC_Init_TxStruct, ADC_Init_RxStruct, adc_num)
    if (0 > ret):
        print("error: %d"%ret)
        
    #读取ADC0
    ADC_Read_TxStruct = (ADC_Read_TxStruct_t*adc_num)()
    ADC_Read_RxStruct = (ADC_Read_RxStruct_t*adc_num)()
    for i in range(adc_num):
        ADC_Read_TxStruct[i].Channel = i
    ret = ADC_ReadMulti(sn, ADC_Read_TxStruct, ADC_Read_RxStruct, adc_num)
    if (0 > ret):
        print("error: %d"%ret)
    else:
        for i in range(adc_num):
            print("ADC[%d] Value: %d"%(i,ADC_Read_RxStruct[i].Value))

    # 关闭设备
    ret = Device_Close(sn)
    if (0 > ret):
        print("error: %d"%ret)

    
