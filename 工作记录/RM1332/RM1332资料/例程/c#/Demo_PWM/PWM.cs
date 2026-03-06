using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class pwm
    {
		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Init_TxStruct
		{
			public byte Channel;
            public uint Frequency;      // 频率Hz
            public ushort Duty;         // 占空比。千分比
            public ushort Phase;        // 相位。千分比
			public byte Polarity;       // 波形极性，取值0或者1
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Init_RxStruct
		{
			public byte Ret;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Start_TxStruct
		{
			public byte Channel;
			public uint RunTimeUs;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Start_RxStruct
		{
			public byte Ret;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Stop_TxStruct
		{
			public byte Channel;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Stop_RxStruct
		{
			public byte Ret;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_SetDuty_TxStruct
		{
			public byte Channel;
			public ushort Duty;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_SetDuty_RxStruct
		{
			public byte Ret;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_SetPhase_TxStruct
		{
			public byte Channel;
			public ushort Phase;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_SetPhase_RxStruct
		{
			public byte Ret;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_SetFrequency_TxStruct
		{
			public byte Channel;
            public uint Frequency;	// 频率Hz
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_SetFrequency_RxStruct
		{
			public byte Ret;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Start_withList_TxStruct
		{
            public byte Channel;
            public uint Frequency;	// 频率Hz
			public ushort Duty;
			public ushort WaveCount;
		};

		[StructLayout(LayoutKind.Sequential)]
		public struct PWM_Start_withList_RxStruct
		{
			public byte Ret;
		};

        // 初始化PWM
        // SerialNumber: 设备序号
        // Channel: 通道编号。0，PWM0. 1, PWM1 ...
        // Frequency：频率/Hz。最小1Hz, 最大1MHz
        // Duty: 占空比。千分比0~1000
        // Phase: 波形相位。千分比0~1000
        // Polarity: 波形极性。范围0~1。
        [DllImport("librockmong.dll")]
        public static extern int PWM_Init(int SerialNumber, int Channel, int Frequency, int Duty, int Phase, int Polarity);

        // PWM开始输出
        // Channel: 通道编号。0，PWM0. 1, PWM1 ...
        // RunTimeUs: 输出波形的时间，单位为微妙，启动波形输出之后，RunTimeOfUs微妙之后会停止波形输出，该参数为0，波形会一直输出，直到手动停止，利用该参数可以控制脉冲输出个数。
        // 函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int PWM_Start(int SerialNumber, int Channel, int RunTimeUs);


        // PWM停止输出
        // Channel: 通道编号。0，PWM0. 1, PWM1 ...
        // 函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int PWM_Stop(int SerialNumber, int Channel);


        // PWM占空比动态调节。可以在PWM启动之后调用
        // Channel: 通道编号。0，PWM0. 1, PWM1 ...
        // Duty: 占空比。范围0~Precision。实际占空比=(Duty/Precision)*100%
        // 函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int PWM_SetDuty(int SerialNumber, int Channel, int Duty);


        // PWM频率动态调节。可以在PWM启动之后调用
        // Channel: 通道编号。0，PWM0. 1, PWM1 ...
        // Frequency：频率/Hz。最小1Hz, 最大1MHz
        // 函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int PWM_SetFrequency(int SerialNumber, int Channel, int Frequency);
		
		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int PWM_InitMulti(int SerialNumber, [In] PWM_Init_TxStruct[] TxStruct, [Out] PWM_Init_RxStruct[] RxStruct, int Number);

		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
		public static extern int PWM_StartMulti(int SerialNumber, [In] PWM_Start_TxStruct[] TxStruct, [Out] PWM_Start_RxStruct[] RxStruct, int Number);

		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
		public static extern int PWM_StopMulti(int SerialNumber, [In] PWM_Stop_TxStruct[] TxStruct, [Out] PWM_Stop_RxStruct[] RxStruct, int Number);

		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
		public static extern int PWM_SetDutyMulti(int SerialNumber, [In] PWM_SetDuty_TxStruct[] TxStruct, [Out] PWM_SetDuty_RxStruct[] RxStruct, int Number);

		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
		public static extern int PWM_SetPhaseMulti(int SerialNumber, [In] PWM_SetPhase_TxStruct[] TxStruct, [Out] PWM_SetPhase_RxStruct[] RxStruct, int Number);

		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
		public static extern int PWM_SetFrequencyMulti(int SerialNumber, [In] PWM_SetFrequency_TxStruct[] TxStruct, [Out] PWM_SetFrequency_RxStruct[] RxStruct, int Number);

		[DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
		public static extern int PWM_Start_withList(int SerialNumber, [In] PWM_Start_withList_TxStruct[] TxStruct, [Out] PWM_Start_withList_RxStruct[] RxStruct, int Number);
    }
}