#include "stdio.h"
#include "usb_device.h"
#include "io.h"
#include "adc.h"
#include "pwm.h"

int main(void)
{
	int ret = 0, i;
	int SerialNumbers[16];
	int Value = 0;
	
	ret = UsbDevice_Scan(SerialNumbers);
	if (ret < 0)
	{
		printf("Scan error: %d\n", ret);
		return ret;
	}
	else if (ret == 0)
	{
		printf("No device\n");
		return ret;
	}
	else
	{
		for (i = 0; i < ret; i++)
		{
			printf("Dev%d SN: %d\n", i, SerialNumbers[i]);
		}
	}

	// 初始化PWM
	// SerialNumber: SerialNumbers[0]
	// Channel: 通道编号。0，PWM0. 
	// Frequency：频率/Hz。最小1Hz, 最大1MHz。1000即1KHz
	// Duty: 占空比。范围0~1000。500即50%
	// Phase: 波形相位。范围0~1000。
	// Polarity: 波形极性。范围0~1。
	// 函数返回：0，正常；<0，异常
	ret = PWM_Init(SerialNumbers[0], 0, 1000, 500, 0, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//PWM开始输出
	ret = PWM_Start(SerialNumbers[0], 0, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//PWM停止输出
	ret = PWM_Stop(SerialNumbers[0], 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
}
