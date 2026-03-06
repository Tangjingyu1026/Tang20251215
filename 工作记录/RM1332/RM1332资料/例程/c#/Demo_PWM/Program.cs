using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Rockmong;

namespace Demo_PWM
{
    class Program
    {
        static void Main(string[] args)
        {
            int ret = 0, i;
            int[] SerialNumbers = new int[16];
            int Value = 0;
	
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

            int sn = SerialNumbers[0];

            ret = device.Device_Open(sn);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }
	
            //初始化PWM0，频率=1KHz，占空比50%
            ret = pwm.PWM_Init(sn, 0, 1000, 500, 0, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //开始PWM0输出
            ret = pwm.PWM_Start(sn, 0, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            //停止PWM0输出
            ret = pwm.PWM_Stop(sn, 0);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }

            ret = device.Device_Close(sn);
            if (ret < 0)
            {
                Console.WriteLine("Error: " + ret.ToString());
            }
        }
    }
}
