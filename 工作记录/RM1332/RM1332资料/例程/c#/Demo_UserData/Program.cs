using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Rockmong;

namespace Demo_UserData
{
    class Program
    {
        static void Main(string[] args)
        {
            int ret = 0, i;
            int[] SerialNumbers = new int[16];
            int addr = 100;
            int size = 256;
            byte[] writeDat = new byte[size];
            byte[] readDat = new byte[size];
	
            ret = usb_device.UsbDevice_Scan(SerialNumbers);
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

            for (i = 0; i < size; i++)
            {
                writeDat[i] = (byte)i;
            }

            //在地址100的位置上，写入256byte数据
            ret = UserData.UserData_Write(SerialNumbers[0], addr, size, writeDat);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //在地址100的位置上，读取256byte数据
            ret = UserData.UserData_Read(SerialNumbers[0], addr, size, readDat);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //比较读取与写入的数据是否一致
            for (i = 0; i < size; i++)
            {
                if (writeDat[i] != readDat[i])
                {
                    Console.WriteLine("Error addr: " + (addr + i).ToString() + " \t" + writeDat[i].ToString() + " != " + readDat[i].ToString());
                }
            }

        }
    }
}
