#-*- coding: utf-8 -*-
from ctypes import *
import platform
from librockmong import *

#修改上电IO口状态
#SerialNumber: 设备序号
#Pin：引脚编号。0，P0. 1, P1...
#Mode：输入输出模式。0，输入。1，输出。2，开漏
#Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
#PinState：引脚状态。0，低电平，1，高电平
#函数返回：0，正常；<0，异常
def PwrOn_IO(SerialNumber, Pin, Mode, Pull):
    return librockmong.PwrOn_IO(SerialNumber, Pin, Mode, Pull, PinState)
	
#修改上电IO口状态
#SerialNumber: 设备序号
#Pin：引脚编号。0，P0. 1, P1...
#Mode：输入输出模式。0，输入。1，输出。2，开漏
#Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
#PinState：引脚状态。0，低电平，1，高电平
#函数返回：0，正常；<0，异常
def PwrOn_PWM(SerialNumber, Pin, Mode, Pull):
    return librockmong.PwrOn_PWM(SerialNumber, Pin, Mode, Pull, PinState)
	
#修改上电IO口状态
#SerialNumber: 设备序号
#Pin：引脚编号。0，P0. 1, P1...
#Mode：输入输出模式。0，输入。1，输出。2，开漏
#Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
#PinState：引脚状态。0，低电平，1，高电平
#函数返回：0，正常；<0，异常
def PwrOn_ADC(SerialNumber, Pin, Mode, Pull):
    return librockmong.PwrOn_ADC(SerialNumber, Pin, Mode, Pull, PinState)
	
class PwrOn_IO_Multi_TxStruct_t(Structure):  
	_fields_ = [
		("Pin", c_ubyte),	# 引脚编号
		("Mode", c_ubyte),	# 模式：0，输入；1，输出
		("Pull", c_ubyte),
		("PinState", c_ubyte),
	]

class PwrOn_IO_Multi_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	# 返回
	]
	
def PwrOn_IO_Multi(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.PwrOn_IO_Multi(SerialNumber, TxStruct, RxStruct, Number)
	
class PwrOn_PWM_Multi_TxStruct_t(Structure):  
	_fields_ = [
		("Channel", c_ubyte),		# 通道编号
		("Prescaler", c_ushort),	# 预分频器
		("Precision", c_ushort),	# 脉冲精度
		("Duty", c_ushort),			# 占空比
		("Phase", c_ushort),		# 波形相位
		("Polarity", c_ubyte),		# 波形极性
	]

class PwrOn_PWM_Multi_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	# 返回
	]
	
def PwrOn_PWM_Multi(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.PwrOn_PWM_Multi(SerialNumber, TxStruct, RxStruct, Number)
	
class PwrOn_ADC_Multi_TxStruct_t(Structure):  
	_fields_ = [
		("Channel", c_ubyte),	# 引脚编号
		("SampleRateHz", c_uint),	# 模式：0，输入；1，输出
	]

class PwrOn_ADC_Multi_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	# 返回
	]
	
def PwrOn_ADC_Multi(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.PwrOn_ADC_Multi(SerialNumber, TxStruct, RxStruct, Number)
	
	
	
	