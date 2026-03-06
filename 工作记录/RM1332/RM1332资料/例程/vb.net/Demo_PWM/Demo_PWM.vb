Module Demo_PWM
	'若运行程序提示找不到librockmong.dll文件，请将librockmong.dll文件和libusb-1.0.dll文件拷贝到exe程序输出目录下，比如bin/Debug目录下
    Sub Main()
        Dim i As UInt32
        Dim ret As Int32
        Dim SerialNumbers(16) as UInt32
        Dim sn As UInt32

        '扫描设备
        ret = UsbDevice_Scan(SerialNumbers)
        If ret < 0 Then
            Console.WriteLine("Scan error: " + ret.ToString())
            Return
        ElseIf ret = 0 Then
            Console.WriteLine("No device")
            Return
        Else
            For i = 0 To ret - 1
                Console.WriteLine("Dev" + i.ToString() + " SN: " + SerialNumbers(i).ToString())
            Next
        End If

        sn = SerialNumbers(0)

        '初始化PWM
        'SerialNumber: SerialNumbers(0)
        'Channel: 通道编号。0，PWM0. 
        'Frequency：频率/Hz。最小1Hz, 最大1MHz。1000即1KHz
        'Duty: 占空比。范围0~1000。500即50%
        'Phase: 波形相位。范围0~1000。
        'Polarity: 波形极性。范围0~1。
        '函数返回：0，正常；<0，异常
        ret = PWM_Init(sn, 0, 1000, 500, 0, 0)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If

        'PWM开始输出
        ret = PWM_Start(sn, 0, 0)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If

        'PWM停止输出
        ret = PWM_Stop(sn, 0)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If
    End Sub

End Module
