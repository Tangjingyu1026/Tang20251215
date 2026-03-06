#-*- coding: utf-8 -*-
from ctypes import *
import platform
from librockmong import *

def iap_jump_boot(SerialNumber):
    return librockmong.iap_jump_boot(SerialNumber)

def iap_write_app(SerialNumber, address, data, length):
    return librockmong.iap_write_app(SerialNumber, address, data, length)

def iap_jump_app(SerialNumber):
    return librockmong.iap_jump_app(SerialNumber)
	
	