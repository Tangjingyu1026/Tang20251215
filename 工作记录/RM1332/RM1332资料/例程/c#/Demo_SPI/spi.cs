using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class spi
    {
        //初始化SPI
        //SerialNumber: 设备序号
        //Channel：通道编号。0，通道0。1，通道1...
        //Mode：模式
        //BaudRate：波特率
        //CPHA：时钟相位
        //CPOL：时钟极性
        //SelPolarity：片选极性
        //函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int SPI_Init(int SerialNumber, int Channel, int Mode, int BaudRate, int CPHA, int CPOL, int SelPolarity);
        
        //写入字节
        //SerialNumber: 设备序号
        //Channel：通道编号
        //WriteBuffer：写入缓冲区
        //WriteLength：写入长度
        //函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int SPI_WriteBytes(int SerialNumber, int Channel, [In] byte[] WriteBuffer, int WriteLength);
        
        //读取字节
        //SerialNumber: 设备序号
        //Channel：通道编号
        //ReadBuffer：读取缓冲区
        //ReadLength：读取长度
        //函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int SPI_ReadBytes(int SerialNumber, int Channel, [Out] byte[] ReadBuffer, int ReadLength);
        
        //同时写入和读取字节
        //SerialNumber: 设备序号
        //Channel：通道编号
        //WriteBuffer：写入缓冲区
        //ReadBuffer：读取缓冲区
        //WriteLength：写入长度
        //ReadLength：读取长度
        //函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int SPI_WriteReadBytes(int SerialNumber, int Channel, [In] byte[] WriteBuffer, [Out] byte[] ReadBuffer, int WriteLength, int ReadLength);
    }
}