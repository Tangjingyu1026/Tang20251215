using System;
using System.Runtime.InteropServices;

namespace Rockmong
{
    class usb_device
    {
        //扫描USB设备
        //返回值如果大于0，代表获取到设备的个数。如果等于0，代表未插入设备。如果小于0，代表发生错误
        [DllImport("librockmong.dll")]
        public static extern int UsbDevice_Scan(int[] SerialNumbers);
    }
}