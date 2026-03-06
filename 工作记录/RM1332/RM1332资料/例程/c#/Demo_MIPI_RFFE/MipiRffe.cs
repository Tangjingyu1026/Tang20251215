using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class MipiRffe
    {
        //初始通道
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //Frequency：频率，单位Hz
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int RFFE_Init(int SerialNumber, int Channel, int Frequency);
        
        //写寄存器0
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //SlaveAddress：从机地址
        //Value：写入值
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int RFFE_Reg0_Write(int SerialNumber, int Channel, int SlaveAddress, int Value);

        //写寄存器
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //SlaveAddress：从机地址
        //RegisterAddress：寄存器地址
        //Value：写入值
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int RFFE_Reg_Write(int SerialNumber, int Channel, int SlaveAddress, int RegisterAddress, int Value);

        //读取寄存器
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //SlaveAddress：从机地址
        //RegisterAddress：寄存器地址
        //Value：返回值
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int RFFE_Reg_Read(int SerialNumber, int Channel, int SlaveAddress, int RegisterAddress, ref int Value);
        
        //写扩展寄存器
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //SlaveAddress：从机地址
        //RegisterAddress：寄存器地址
        //WriteBuffer：写入值
        //WriteLength：写入长度
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int RFFE_Ext_Reg_Write(int SerialNumber, int Channel, int SlaveAddress, int RegisterAddress, [In] byte[] WriteBuffer, int WriteLength);

        //读取寄存器
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //SlaveAddress：从机地址
        //RegisterAddress：寄存器地址
        //ReadBuffer：返回值
        //ReadLength：读取长度
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int RFFE_Ext_Reg_Read(int SerialNumber, int Channel, int SlaveAddress, int RegisterAddress, [Out] byte[] ReadBuffer, int ReadLength);


    }
}