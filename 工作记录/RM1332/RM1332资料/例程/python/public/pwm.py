#-*- coding: utf-8 -*-
from ctypes import *
from librockmong import *

# 初始化PWM
# SerialNumber: 设备序号
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# Prescaler: 预分频器。范围1~65535
# Precision: 脉冲精度。范围1~65535. PWM频率=72MHz/(Prescaler*Precision)
# Duty: 占空比。范围0~Precision。实际占空比=(Duty/Precision)*100%
# Phase: 波形相位。范围0~Precision-1。
# Polarity: 波形极性。范围0~1。
# 函数返回：0，正常；<0，异常
def PWM_Init(SerialNumber, Channel, Frequency, Duty, Phase, Polarity):
    return librockmong.PWM_Init(SerialNumber, Channel, Frequency, Duty, Phase, Polarity)

# PWM开始输出
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# RunTimeUs: 输出波形的时间，单位为微妙，启动波形输出之后，RunTimeOfUs微妙之后会停止波形输出，该参数为0，波形会一直输出，直到手动停止，利用该参数可以控制脉冲输出个数。
# 函数返回：0，正常；<0，异常
def PWM_Start(SerialNumber, Channel, RunTimeUs):
    return librockmong.PWM_Start(SerialNumber, Channel, RunTimeUs)

# PWM停止输出
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# 函数返回：0，正常；<0，异常
def PWM_Stop(SerialNumber, Channel):
    return librockmong.PWM_Stop(SerialNumber, Channel)

# PWM占空比动态调节。可以在PWM启动之后调用
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# Duty: 占空比。范围0~Precision。实际占空比=(Duty/Precision)*100%
# 函数返回：0，正常；<0，异常
def PWM_SetDuty(SerialNumber, Channel, Duty):
    return librockmong.PWM_SetDuty(SerialNumber, Channel, Duty)

# PWM频率动态调节。可以在PWM启动之后调用
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# Prescaler: 预分频器。范围1~65535
# Precision: 脉冲精度。范围1~65535
# 函数返回：0，正常；<0，异常
def PWM_SetFrequency(SerialNumber, Channel, Frequency):
    return librockmong.PWM_SetFrequency(SerialNumber, Channel, Frequency)
	
# PWM频率动态调节。可以在PWM启动之后调用，频率比较大的时候，设置的参数可能跟实际输出的值误差较大，建议根据实际输出值对该参数进行调整。
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# Prescaler: 预分频器。范围1~65535
# Precision: 脉冲精度。范围1~65535
# 函数返回：0，正常；<0，异常
def PWM_SetPhase(SerialNumber, Channel, Phase):
    return librockmong.PWM_SetPhase(SerialNumber, Channel, Phase)

class PWM_Start_withList_TxStruct_t(Structure):  
	_fields_ = [
		("Channel", c_ubyte),		# 通道编号
		("Frequency", c_uint32),		# 频率
		("Duty", c_ushort),			# 占空比
		("WaveCount", c_ushort),	# 波的个数
	]

class PWM_Start_withList_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	#返回
	]

# PWM列表输出。可以控制脉冲频率、占空比和波的个数
# Channel: 通道编号。0，PWM0. 1, PWM1 ...
# TxStruct: 发送结构体数组
# RxStruct: 返回结构体数组
# 函数返回：0，正常；<0，异常
def PWM_Start_withList(SerialNumber, TxStruct, RxStruct, Number):
	return librockmong.PWM_Start_withList(SerialNumber, TxStruct, RxStruct, Number)