using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class adc
    {
        //初始化ADC通道
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0. 1, 通道1...
        //SampleRateHz：采样率，一般设置0
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int ADC_Init(int SerialNumber, int Channel, int SampleRateHz);

        //读取引脚状态
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0. 1, 通道1...
        //Value：返回ADC值
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int ADC_Read(int SerialNumber, int Channel, ref int Value);
    }
}