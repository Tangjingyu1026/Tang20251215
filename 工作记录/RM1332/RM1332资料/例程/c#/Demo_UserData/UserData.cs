using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class UserData
    {
       

        //擦除所有用户数据
        //SerialNumber: 设备序号
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int UserData_Erase(int SerialNumber);

        //写入用户数据
        //SerialNumber: 设备序号
        //Address：数据地址。
        //Size：要写入数据的大小。
        //Dat：写入的数据
		//函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int UserData_Write(int SerialNumber, int Address, int Size, [In] byte[] Dat);

        //读取用户数据
        //SerialNumber: 设备序号
        //Address：数据地址。
        //Size：要读取数据的大小。
        //Dat：读取的数据
        //函数返回：0，正常；<0，异常
        [DllImport("librockmong.dll", CallingConvention = CallingConvention.Winapi)]
        public static extern int UserData_Read(int SerialNumber, int Address, int Size, [Out] byte[] Dat);

    
    }
}