Imports System.Runtime.InteropServices
Module pwm

    '初始化PWM
    'SerialNumber: 设备序号
    'Channel: 通道编号。0，PWM0. 1, PWM1 ...
    'Frequency：频率/Hz。最小1Hz, 最大1MHz
    'Duty: 占空比。千分比0~1000
    'Phase: 波形相位。千分比0~1000
    'Polarity: 波形极性。范围0~1。
    '函数返回：0，正常；<0，异常
    Declare Function PWM_Init Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32, ByVal Frequency As UInt32, ByVal Duty As UInt16, ByVal Phase As UInt16, ByVal Polarity As Byte) As Int32

    'PWM开始输出
    'SerialNumber: 设备序号
    'Channel: 通道编号。0，PWM0. 1, PWM1 ...
    'RunTimeUs: 输出波形的时间，单位为微妙，启动波形输出之后，RunTimeOfUs微妙之后会停止波形输出，该参数为0，波形会一直输出，直到手动停止，利用该参数可以控制脉冲输出个数。
    '函数返回：0，正常；<0，异常
    Declare Function PWM_Start Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32, ByVal RunTimeUs As UInt32) As Int32

    'PWM停止输出
    'SerialNumber: 设备序号
    'Channel: 通道编号。0，PWM0. 1, PWM1 ...
    '函数返回：0，正常；<0，异常
    Declare Function PWM_Stop Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32) As Int32

    'PWM占空比动态调节。可以在PWM启动之后调用
    'SerialNumber: 设备序号
    'Channel: 通道编号。0，PWM0. 1, PWM1 ...
    'Duty: 占空比。千分比0~1000
    '函数返回：0，正常；<0，异常
    Declare Function PWM_SetDuty Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32, ByVal Duty As UInt16) As Int32

    'PWM频率动态调节。可以在PWM启动之后调用
    'SerialNumber: 设备序号
    'Channel: 通道编号。0，PWM0. 1, PWM1 ...
    'Frequency：频率/Hz。最小1Hz, 最大1MHz
    '函数返回：0，正常；<0，异常
    Declare Function PWM_SetFrequency Lib "librockmong.dll" (ByVal SerialNumber As UInt32, ByVal Channel As UInt32, ByVal Frequency As UInt32) As Int32

End Module

