using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Rockmong;

namespace Demo_IO
{
    class Program
    {
        static void Main(string[] args)
        {
            int ret = 0, i;
            int[] SerialNumbers = new int[16];
            int PinState = 0;
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

            ret = device.Device_Open(sn);
            if (ret < 0)
            {
                Console.Write("Open error: %d\n", ret);
                return;
            }
	
            //P0初始化为输出模式
            ret = io.IO_InitPin(sn, 0, 1, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //P0输出低电平
            ret = io.IO_WritePin(sn, 0, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //P0输出高电平
            ret = io.IO_WritePin(sn, 0, 1);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //P0初始化为输入模式
            ret = io.IO_InitPin(sn, 0, 0, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //读取P0状态
            ret = io.IO_ReadPin(sn, 0, ref PinState);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }
            Console.WriteLine("Read pin: " + PinState.ToString());

            ret = device.Device_Close(sn);
            if (ret < 0)
            {
                Console.Write("Close error: %d\n", ret);
                return;
            }
        }
    }
}
