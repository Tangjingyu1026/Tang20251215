#-*- coding: utf-8 -*-
from ctypes import *
from librockmong import *

# 初始化ADC
# SerialNumber: 设备序号
# Channel: 通道编号。0，ADC0. 1, ADC1 ...
# SampleRateHz：ADC采样频率，一般设置0
# 函数返回：0，正常；<0，异常
def ADC_Init(SerialNumber, Channel, SampleRateHz):
    return librockmong.ADC_Init(SerialNumber, Channel, SampleRateHz)

# ADC读取
# Channel: 通道编号。0，ADC0. 1, ADC1 ...
# Value: AD值
# 函数返回：0，正常；<0，异常
def ADC_Read(SerialNumber, Channel, Value):
    return librockmong.ADC_Read(SerialNumber, Channel, Value)

class ADC_Init_TxStruct_t(Structure):  
	_fields_ = [
		("Channel", c_ubyte),		# 通道编号
		("SampleRateHz", c_uint32),	# 采样率
	]

class ADC_Init_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	#返回
	]
        
def ADC_InitMulti(SerialNumber, TxStruct, RxStruct, Number):
	return librockmong.ADC_InitMulti(SerialNumber, TxStruct, RxStruct, Number)

class ADC_Read_TxStruct_t(Structure):  
	_fields_ = [
		("Channel", c_ubyte),		# 通道编号
	]

class ADC_Read_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	    #返回
		("Value", c_uint16),	#ADC数值
	]
	
def ADC_ReadMulti(SerialNumber, TxStruct, RxStruct, Number):
	return librockmong.ADC_ReadMulti(SerialNumber, TxStruct, RxStruct, Number)
