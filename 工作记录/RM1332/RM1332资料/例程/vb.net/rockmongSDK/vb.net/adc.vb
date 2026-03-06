Imports System.Runtime.InteropServices
Module adc

    '初始化ADC
    'SerialNumber: 设备序号
    'Channel：通道编号。0，ADC0. 1, ADC1...
    'SampleRateHz：采样率。一般设置0
    '函数返回：0，正常；<0，异常
    Declare Function ADC_Init Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32, ByVal SampleRateHz As UInt32) As Int32

    'ADC读取
    'SerialNumber: 设备序号
    'Channel：通道编号。0，ADC0. 1, ADC1...
    'Value：AD值
    '函数返回：0，正常；<0，异常
    Declare Function ADC_Read Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32, <Out()> ByVal Value As UInt32()) As Int32

End Module

