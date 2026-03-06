#-*- coding: utf-8 -*-
from ctypes import *
import platform
from librockmong import *

#初始化引脚工作模式
#SerialNumber: 设备序号
#Pin：引脚编号。
#Mode：输入输出模式。0，输入。1，输出。2，开漏
#Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
#函数返回：0，正常；<0，异常
def IO_InitPin(SerialNumber, Pin, Mode, Pull):
    return librockmong.IO_InitPin(SerialNumber, Pin, Mode, Pull)
    
#读取引脚状态
#SerialNumber: 设备序号
#Pin：引脚编号。
#PinState：返回引脚状态。0，低电平。1，高电平
#函数返回：0，正常；<0，异常
def IO_ReadPin(SerialNumber, Pin, PinState):
    return librockmong.IO_ReadPin(SerialNumber, Pin, PinState)

#控制引脚输出状态
#SerialNumber: 设备序号
#Pin：引脚编号。
#PinState：引脚状态。0，低电平。1，高电平
#函数返回：0，正常；<0，异常
def IO_WritePin(SerialNumber, Pin, PinState):
    return librockmong.IO_WritePin(SerialNumber, Pin, PinState)
    
#读取输出引脚状态
#SerialNumber: 设备序号
#Pin：引脚编号。
#PinState：返回引脚状态。0，低电平。1，高电平
#函数返回：0，正常；<0，异常
def IO_ReadOutputPin(SerialNumber, Pin, PinState):
    return librockmong.IO_ReadOutputPin(SerialNumber, Pin, PinState)

class IO_InitMultiPin_TxStruct_t(Structure):  
	_fields_ = [
		("Pin", c_ubyte),	# 引脚编号
		("Mode", c_ubyte),	# 模式：0，输入；1，输出
		("Pull", c_ubyte)
	]

class IO_InitMultiPin_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	# 返回
	]
    
def IO_InitMultiPin(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.IO_InitMultiPin(SerialNumber, TxStruct, RxStruct, Number)


class IO_ReadMultiPin_TxStruct_t(Structure):  
	_fields_ = [
		("Pin", c_ubyte),	# 引脚编号
	]

class IO_ReadMultiPin_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),		# 返回
		("PinState", c_ubyte),	# 引脚状态
	]
    
def IO_ReadMultiPin(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.IO_ReadMultiPin(SerialNumber, TxStruct, RxStruct, Number)


class IO_WriteMultiPin_TxStruct_t(Structure):  
	_fields_ = [
		("Pin", c_ubyte),		# 引脚编号
		("PinState", c_ubyte),	# 引脚状态
	]

class IO_WriteMultiPin_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),	#返回
	]
    
def IO_WriteMultiPin(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.IO_WriteMultiPin(SerialNumber, TxStruct, RxStruct, Number)
	
	
class IO_ReadMultiOutputPin_TxStruct_t(Structure):  
	_fields_ = [
		("Pin", c_ubyte),	# 引脚编号
	]

class IO_ReadMultiOutputPin_RxStruct_t(Structure):  
	_fields_ = [
		("Ret", c_ubyte),		# 返回
		("PinState", c_ubyte),	# 引脚状态
	]
    
def IO_ReadMultiOutputPin(SerialNumber, TxStruct, RxStruct, Number):
    return librockmong.IO_ReadMultiOutputPin(SerialNumber, TxStruct, RxStruct, Number)
	
