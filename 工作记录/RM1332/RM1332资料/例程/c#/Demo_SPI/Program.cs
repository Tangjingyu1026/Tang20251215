using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Rockmong;

/// <summary>
/// 本示例代码用于测试SPI模块通信
/// 接线：根据硬件连接配置SPI通道
/// 程序：初始化SPI，写入数据，读取数据
/// </summary>


namespace Demo_SPI
{
    class Program
    {
        static void Main(string[] args)
        {
            int ret = 0, i;
            int[] SerialNumbers = new int[16];
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
            int spi_channel = 0;
            int spi_mode = 0;
            int spi_baudrate = 1000000; // 1MHz
            int spi_cpha = 0;
            int spi_cpol = 0;
            int spi_sel_polarity = 0;

            ret = device.Device_Open(sn);
            if (ret < 0)
            {
                Console.Write("Open error: %d\n", ret);
                return;
            }
	
            //初始化SPI
            ret = spi.SPI_Init(sn, spi_channel, spi_mode, spi_baudrate, spi_cpha, spi_cpol, spi_sel_polarity);
            if (ret < 0)
            {
                Console.WriteLine("SPI Init Error: " + ret.ToString());
                device.Device_Close(sn);
                return;
            }
            Console.WriteLine("SPI initialized successfully");

            //准备写入数据
            byte[] writeBuffer = new byte[] { 0x01, 0x02, 0x03 };
            ret = spi.SPI_WriteBytes(sn, spi_channel, writeBuffer, writeBuffer.Length);
            if (ret < 0)
            {
                Console.WriteLine("SPI Write Error: " + ret.ToString());
            }
            else
            {
                Console.WriteLine("SPI Write successful, wrote " + writeBuffer.Length + " bytes");
            }

            //读取数据
            byte[] readBuffer = new byte[4];
            ret = spi.SPI_ReadBytes(sn, spi_channel, readBuffer, readBuffer.Length);
            if (ret < 0)
            {
                Console.WriteLine("SPI Read Error: " + ret.ToString());
            }
            else
            {
                Console.Write("SPI Read successful, read " + readBuffer.Length + " bytes: ");
                for (i = 0; i < readBuffer.Length; i++)
                {
                    Console.Write("0x" + readBuffer[i].ToString("X2") + " ");
                }
                Console.WriteLine();
            }

            //同时写入和读取数据
            byte[] writeReadBuffer = new byte[] { 0xAA, 0xBB };
            byte[] readReadBuffer = new byte[2];
            ret = spi.SPI_WriteReadBytes(sn, spi_channel, writeReadBuffer, readReadBuffer, writeReadBuffer.Length, readReadBuffer.Length);
            if (ret < 0)
            {
                Console.WriteLine("SPI WriteRead Error: " + ret.ToString());
            }
            else
            {
                Console.Write("SPI WriteRead successful, read " + readReadBuffer.Length + " bytes: ");
                for (i = 0; i < readReadBuffer.Length; i++)
                {
                    Console.Write("0x" + readReadBuffer[i].ToString("X2") + " ");
                }
                Console.WriteLine();
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
