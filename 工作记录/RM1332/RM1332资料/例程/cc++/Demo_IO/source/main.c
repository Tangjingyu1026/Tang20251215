#include "stdio.h"
#include "usb_device.h"
#include "io.h"

int main(void)
{
	int ret = 0, i;
	int SerialNumbers[16];
	int PinState = 0;
	
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
	
	//P0初始化为输出模式
	ret = IO_InitPin(SerialNumbers[0], 0, 1, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0输出低电平
	ret = IO_WritePin(SerialNumbers[0], 0, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0输出高电平
	ret = IO_WritePin(SerialNumbers[0], 0, 1);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0初始化为输入模式
	ret = IO_InitPin(SerialNumbers[0], 0, 0, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//读取P0状态
	ret = IO_ReadPin(SerialNumbers[0], 0, &PinState);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	printf("Read pin: %d", PinState);
}
