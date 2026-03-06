Attribute VB_Name = "pwm"

' 初始化PWM
' SerialNumber: 设备序号
' Channel: 通道编号。0，PWM0. 1, PWM1 ...
' Frequency：频率/Hz。最小1Hz, 最大1MHz
' Duty: 占空比。千分比0~1000
' Phase: 波形相位。范围0~Precision-1。
' Polarity: 波形极性。范围0~1。
' 函数返回：0，正常；<0，异常
Declare Function PWM_Init Lib "librockmong.dll" (ByVal SerialNumber As Long, ByVal Channel As Long, ByVal Frequency As Long, ByVal Duty As Long, ByVal Phase As Long, ByVal Polarity As Long) As Long

' PWM开始输出
' Channel: 通道编号。0，PWM0. 1, PWM1 ...
' RunTimeUs: 输出波形的时间，单位为微妙，启动波形输出之后，RunTimeOfUs微妙之后会停止波形输出，该参数为0，波形会一直输出，直到手动停止，利用该参数可以控制脉冲输出个数。
' 函数返回：0，正常；<0，异常
Declare Function PWM_Start Lib "librockmong.dll" (ByVal SerialNumber As Long, ByVal Channel As Long, ByVal RunTimeUs As Long) As Long

' PWM停止输出
' Channel: 通道编号。0，PWM0. 1, PWM1 ...
' 函数返回：0，正常；<0，异常
Declare Function PWM_Stop Lib "librockmong.dll" (ByVal SerialNumber As Long, ByVal Channel As Long) As Long

' PWM占空比动态调节。可以在PWM启动之后调用
' Channel: 通道编号。0，PWM0. 1, PWM1 ...
' Duty: 占空比。千分比0~1000
' 函数返回：0，正常；<0，异常
Declare Function PWM_SetDuty Lib "librockmong.dll" (ByVal SerialNumber As Long, ByVal Channel As Long, ByVal Duty As Long) As Long

' PWM频率动态调节。可以在PWM启动之后调用
' Channel: 通道编号。0，PWM0. 1, PWM1 ...
' Frequency：频率/Hz。最小1Hz, 最大1MHz
' 函数返回：0，正常；<0，异常
Declare Function PWM_SetFrequency Lib "librockmong.dll" (ByVal SerialNumber As Long, ByVal Channel As Long, ByVal Frequency As Long) As Long
