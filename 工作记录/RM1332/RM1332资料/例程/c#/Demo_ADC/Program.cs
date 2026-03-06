using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Rockmong;

namespace Demo_ADC
{
    class Program
    {
        static void Main(string[] args)
        {
            int ret = 0, i;
            int[] SerialNumbers = new int[16];
            int Value = 0;
	
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
	
            //初始化ADC0
            ret = adc.ADC_Init(SerialNumbers[0], 0, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //读取ADC0
            ret = adc.ADC_Read(SerialNumbers[0], 0, ref Value);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }
            Console.WriteLine("Read adc: " + Value.ToString());
        }
    }
}
