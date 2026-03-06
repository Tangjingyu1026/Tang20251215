Attribute VB_Name = "Demo_PWM"
Public Declare Function AllocConsole Lib "kernel32.dll" () As Long
Public Declare Function FreeConsole Lib "kernel32.dll" () As Long
Public Declare Function SetConsoleTitle Lib "kernel32.dll" Alias "SetConsoleTitleA" (ByVal lpConsoleTitle As String) As Long
Public Declare Sub Sleep Lib "kernel32.dll" (ByVal dwMilliseconds As Long)

Private Declare Function GetStdHandle Lib "kernel32.dll" (ByVal nStdHandle As Long) As Long

Private Declare Function WriteConsole Lib "kernel32.dll" Alias "WriteConsoleA" _
                                                (ByVal hConsoleOutput As Long, _
                                                 lpBuffer As Any, _
                                                 ByVal nNumberOfCharsToWrite As Long, _
                                                 lpNumberOfCharsWritten As Long, _
                                                 lpReserved As Any) As Long
                                                 
Private Declare Function ReadConsole Lib "kernel32.dll" Alias "ReadConsoleA" _
                                                (ByVal hConsoleInput As Long, _
                                                lpBuffer As Any, _
                                                ByVal nNumberOfCharsToRead As Long, _
                                                lpNumberOfCharsRead As Long, _
                                                lpReserved As Any) As Long
                                                
Private Declare Function SetConsoleMode Lib "kernel32" (ByVal hConsoleHandle As Long, ByVal dwMode As Long) As Long

Private Const INPUT_HANDLE = -10&
Private Const OUTPUT_HANDLE = -11&
Private Const ERROR_HANDLE = -12&

Private Const LINE_INPUT = &H2
Private Const ECHO_INPUT = &H4
Private Const MOUSE_INPUT = &H10
Private Const PROCESSED = &H1

Public Function Printf(ByVal hConsoleOutput As Long, ByVal str As String) As Long
    Call WriteConsole(hConsoleOutput, ByVal str, Len(str), vbNull, vbNull)
End Function

Sub Main()
    Call AllocConsole
    Call SetConsoleTitle("PWM Test")
    
    Dim inputHandle As Long
    Dim str As String
    Dim outputHandle As Long
    Dim ret As Long
    Dim SerialNumbers(20) As Long
    Dim sn As Long
    Dim PinState As Long
    outputHandle = GetStdHandle(OUTPUT_HANDLE)
    
    ret = UsbDevice_Scan(VarPtr(SerialNumbers(0)))
    If ret <= 0 Then
        str = "No device connected! Ret: " + CStr(ret) + vbNewLine
        Call WriteConsole(outputHandle, ByVal str, Len(str), vbNull, vbNull)
        End
    End If
    
    sn = SerialNumbers(0)
    str = "SN: " + CStr(sn) + vbNewLine
    Call WriteConsole(outputHandle, ByVal str, Len(str), vbNull, vbNull)
    
	' 初始化PWM
	' SerialNumber：设备SN号
	' Channel: 通道编号。0，PWM0. 
	' Frequency：频率/Hz。最小1Hz, 最大1MHz。1000即1KHz
	' Duty: 占空比。范围0~1000。500即50%
	' Phase: 波形相位。范围0~1000。
	' Polarity: 波形极性。范围0~1。
	' 函数返回：0，正常；<0，异常
    ret = PWM_Init(sn, 0, 1000, 500, 0, 0)
    If ret < 0 Then
        str = "Error: " + CStr(ret) + vbNewLine
        Call WriteConsole(outputHandle, ByVal str, Len(str), vbNull, vbNull)
        End
    End If
	
	' PWM开始输出
    ret = PWM_Start(sn, 0, 0)
    If ret < 0 Then
        str = "Error: " + CStr(ret) + vbNewLine
        Call WriteConsole(outputHandle, ByVal str, Len(str), vbNull, vbNull)
        End
    End If
	
	' PWM停止输出
    'ret = PWM_Stop(sn, 0)
    'If ret < 0 Then
    '    str = "Error: " + CStr(ret) + vbNewLine
    '    Call WriteConsole(outputHandle, ByVal str, Len(str), vbNull, vbNull)
    '    End
    'End If	
    
    inputHandle = GetStdHandle(INPUT_HANDLE)
    Call ReadConsole(inputHandle, vbNull, 255, vbNull, vbNull)
    Call FreeConsole
End Sub

