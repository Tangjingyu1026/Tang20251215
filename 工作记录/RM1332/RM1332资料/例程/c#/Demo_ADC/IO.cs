using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class io
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct IO_Init_TxStruct
        {
            public byte Pin;
            public byte Mode;
            public byte Pull;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct IO_Init_RxStruct
        {
            public byte Ret;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct IO_Read_TxStruct
        {
            public byte Pin;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct IO_Read_RxStruct
        {
            public byte Ret;
            public byte PinState;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct IO_Write_TxStruct
        {
            public byte Pin;
            public byte PinState;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct IO_Write_RxStruct
        {
            public byte Ret;
        }

        //初始化引脚工作模式
        //SerialNumber: 设备序号
        //Pin：引脚编号。0，P0. 1, P1...
        //Mode：输入输出模式。0，输入。1，输出。2，开漏
        //Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int IO_InitPin(int SerialNumber, int Pin, int Mode, int Pull);

        //读取引脚状态
        //SerialNumber: 设备序号
        //Pin：引脚编号。0，P0. 1, P1...
        //PinState：返回引脚状态。0，低电平。1，高电平
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int IO_ReadPin(int SerialNumber, int Pin, ref int PinState);

        //控制引脚输出状态
        //SerialNumber: 设备序号
        //Pin：引脚编号。0，P0. 1, P1...
        //PinState：引脚状态。0，低电平。1，高电平
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int IO_WritePin(int SerialNumber, int Pin, int PinState);

        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int IO_InitMultiPin(int SerialNumber, [In] IO_Init_TxStruct[] TxStruct, [Out] IO_Init_RxStruct[] RxStruct, int Number);

        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int IO_ReadMultiPin(int SerialNumber, [In] IO_Read_TxStruct[] TxStruct, [Out] IO_Read_RxStruct[] RxStruct, int Number);

        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int IO_WriteMultiPin(int SerialNumber, [In] IO_Write_TxStruct[] TxStruct, [Out] IO_Write_RxStruct[] RxStruct, int Number);
    }
}