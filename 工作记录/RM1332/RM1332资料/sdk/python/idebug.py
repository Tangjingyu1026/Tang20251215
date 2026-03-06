#-*- coding: utf-8 -*-
import ctypes
from ctypes import *
import platform
from librockmong import *

# 声明函数返回类型
librockmong.idebug_get.restype = ctypes.c_char_p

def idebug_enable(enable):
	librockmong.idebug_enable(enable)
	
def idebug_print():
	result = librockmong.idebug_get()
	# 将返回的 char* 转换为 Python 字符串
	result_str = ctypes.string_at(result).decode("utf-8")
    # 打印结果
	print(result_str)