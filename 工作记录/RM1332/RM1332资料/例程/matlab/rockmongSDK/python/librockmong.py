from ctypes import *
import platform
import os
import shutil

current_path = os.path.normpath(os.path.dirname(os.path.abspath(__file__)))

#根据系统自动导入对应的库文件，若没能识别到正确的系统，可以修改下面的源码
if(platform.system()=="Windows"):
    if "64bit" in platform.architecture():
        windll.LoadLibrary(current_path+"/libs/windows/x86_64/libusb-1.0.dll" )
        librockmong = windll.LoadLibrary(current_path+"/libs/windows/x86_64/librockmong.dll" )
    else:
        windll.LoadLibrary(current_path+"/libs/windows/x86/libusb-1.0.dll" )
        librockmong = windll.LoadLibrary(current_path+"/libs/windows/x86/librockmong.dll" )
elif(platform.system()=="Darwin"):
    cdll.LoadLibrary(current_path+"/libs/mac_os/libusb-1.0.0.dylib" )
    librockmong = cdll.LoadLibrary(current_path+"/libs/mac_os/librockmong.dylib" )
elif(platform.system()=="Linux"):
    if 'armv7' in platform.machine():
        cdll.LoadLibrary(current_path+"/libs/linux/armv7/libusb-1.0.so" )
        librockmong = cdll.LoadLibrary(current_path+"/libs/linux/armv7/librockmong.so" )
    elif 'mips64' in platform.machine():
        cdll.LoadLibrary(current_path+"/libs/linux/mips64/libusb-1.0.so" )
        librockmong = cdll.LoadLibrary(current_path+"/libs/linux/mips64/librockmong.so" )
    elif 'aarch64' in platform.machine():
        cdll.LoadLibrary(current_path+"/libs/linux/aarch64/libusb-1.0.so" )
        librockmong = cdll.LoadLibrary(current_path+"/libs/linux/aarch64/librockmong.so" )
    elif 'arm64' in platform.machine():
        cdll.LoadLibrary(current_path+"/libs/linux/arm64/libusb-1.0.so" )
        librockmong = cdll.LoadLibrary(current_path+"/libs/linux/arm64/librockmong.so" )
    else:
        if "64bit" in platform.architecture():
            cdll.LoadLibrary(current_path+"/libs/linux/x86_64/libusb-1.0.so" )
            librockmong = cdll.LoadLibrary(current_path+"/libs/linux/x86_64/librockmong.so" )
        else:
            cdll.LoadLibrary(current_path+"/libs/linux/x86/libusb-1.0.so" )
            librockmong = cdll.LoadLibrary(current_path+"/libs/linux/x86/librockmong.so" )
else:
    print("unsupported system")
    exit()



