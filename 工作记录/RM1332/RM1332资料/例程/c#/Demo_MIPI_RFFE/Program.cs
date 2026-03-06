using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Rockmong;

/// <summary>
/// 本示例代码用于测试MIPI RFFE模块通信
/// 接线：P0接模块的VIO，用于控制模块的开关。模块SCLK接P14，SDATA接P15，也就是IO模块的通信通道7
/// 程序：读取从机0x08的0x1F寄存器
/// </summary>


namespace Demo_MIPI_RFFE
{
    class Program
    {
        static void Main(string[] args)
        {
            int ret = 0, i;
            int[] SerialNumbers = new int[16];
            int value = 0;
            int sn = 0;
	
            ret = device.Device_Scan(SerialNumbers);
            if (ret < 0)
            {
	            Console.Write("Scan error: %d\n", ret);
                return;
            }
            else if (ret == 0)
            {
	            Console.Write("No device\n");
                return;
            }
            else
            {
	            for (i = 0; i < ret; i++)
	            {
		            Console.WriteLine("Dev" + i.ToString() + " SN: " + SerialNumbers[i].ToString());
	            }
            }

            sn = SerialNumbers[0];
            int rffe_channel = 7;
            int rffe_slave_address = 0x08;
            int rffe_register_address = 0x1F;

            ret = device.Device_Open(sn);
            if (ret < 0)
            {
                Console.Write("Open error: %d\n", ret);
                return;
            }
	
            //P0 接 模块的VIO，引脚初始化
            ret = io.IO_InitPin(sn, 0, 1, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //VIO输出低电平
            ret = io.IO_WritePin(sn, 0, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //初始化RFFE
            ret = MipiRffe.RFFE_Init(sn, rffe_channel, 1000000);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //VIO输出高电平
            ret = io.IO_WritePin(sn, 0, 1);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //读取寄存器
            ret = MipiRffe.RFFE_Reg_Read(sn, rffe_channel, rffe_slave_address, rffe_register_address, ref value);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }
            Console.WriteLine("Read value: 0x" + value.ToString("X2"));

            ret = device.Device_Close(sn);
            if (ret < 0)
            {
                Console.Write("Close error: %d\n", ret);
                return;
            }
        }
    }
}
