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
	
            //P1，P4初始化为输入模式，P3, P5初始化为输出模式
            io.IO_Init_TxStruct[] initTx = new io.IO_Init_TxStruct[4];
            io.IO_Init_RxStruct[] initRx = new io.IO_Init_RxStruct[4];
            initTx[0].Pin = 1;
            initTx[0].Mode = 0;
            initTx[0].Pull = 0;
            initTx[1].Pin = 4;
            initTx[1].Mode = 0;
            initTx[1].Pull = 0;
            initTx[2].Pin = 3;
            initTx[2].Mode = 1;
            initTx[2].Pull = 0;
            initTx[3].Pin = 5;
            initTx[3].Mode = 1;
            initTx[3].Pull = 0;
            ret = io.IO_InitMultiPin(sn, initTx, initRx, 4);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //P3输出低电平, P5输出高电平
            io.IO_Write_TxStruct[] writeTx = new io.IO_Write_TxStruct[2];
            io.IO_Write_RxStruct[] writeRx = new io.IO_Write_RxStruct[2];
            writeTx[0].Pin = 3;
            writeTx[0].PinState = 0;
            writeTx[1].Pin = 5;
            writeTx[1].PinState = 1;
            ret = io.IO_WriteMultiPin(SerialNumbers[0], writeTx, writeRx, 2);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //读取P1, P4状态
            io.IO_Read_TxStruct[] ReadTx = new io.IO_Read_TxStruct[2];
            io.IO_Read_RxStruct[] ReadRx = new io.IO_Read_RxStruct[2];
            ReadTx[0].Pin = 1;
            ReadTx[1].Pin = 4;
            ret = io.IO_ReadMultiPin(sn, ReadTx, ReadRx, 2);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }
            for (i = 0; i < 2; i++)
            {
                Console.WriteLine("Read Pin " + ReadTx[i].Pin.ToString() + ": " + ReadRx[i].PinState.ToString());
            }

            ret = device.Device_Close(sn);
            if (ret < 0)
            {
                Console.Write("Close error: %d\n", ret);
                return;
            }
                
        }
    }
}
