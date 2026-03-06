Module Demo_IO
	'若运行程序提示找不到librockmong.dll文件，请将librockmong.dll文件和libusb-1.0.dll文件拷贝到exe程序输出目录下，比如bin/Debug目录下
    Sub Main()
        Dim i As UInt32
        Dim ret As Int32
        Dim SerialNumbers(16) as UInt32
        Dim PinState(1) As UInt32
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

        'P0初始化为输出模式
        ret = IO_InitPin(sn, 0, 1, 0)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If
        
        'P0输出低电平
        ret = IO_WritePin(sn, 0, 0)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If
        
        'P0输出高电平
        ret = IO_WritePin(sn, 0, 1)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If

        'P0初始化为输入模式
        ret = IO_InitPin(sn, 0, 0, 0)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If

        '读取P0状态
        ret = IO_ReadPin(sn, 0, PinState)
        If ret < 0 Then
            Console.WriteLine("Error: " + ret.ToString())
            Return
        End If
        Console.WriteLine("Read pin: " + PinState(0).ToString())
    End Sub

End Module
