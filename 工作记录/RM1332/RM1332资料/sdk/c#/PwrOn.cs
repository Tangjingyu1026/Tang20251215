using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class pwron
    {
        public struct PwrOn_IO_TxStruct
        {
            public byte Pin;
            public byte Mode;
            public byte Pull;
			public byte PinState;
        }

        public struct PwrOn_IO_RxStruct
        {
            public byte Ret;
        }

        //设置上电时IO的状态
        //SerialNumber: 设备序号
        //Pin：引脚编号。0，P0. 1, P1...
        //Mode：输入输出模式。0，输入。1，输出。2，开漏
        //Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
        //PinState：引脚电平。0，低电平。1，高电平
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll")]
        public static extern int PwrOn_IO(int SerialNumber, int Pin, int Mode, int Pull, int PinState);

        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int PwrOn_IO_Multi(int SerialNumber, [In] PwrOn_IO_TxStruct[] TxStruct, [Out] PwrOn_IO_RxStruct[] RxStruct, int Number);

    }
}