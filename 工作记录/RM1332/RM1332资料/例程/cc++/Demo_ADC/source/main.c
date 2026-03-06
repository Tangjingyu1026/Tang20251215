#include "stdio.h"
#include "usb_device.h"
#include "io.h"
#include "adc.h"

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
	
	//初始化ADC0
	ret = ADC_Init(SerialNumbers[0], 0, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//读取ADC0
	ret = ADC_Read(SerialNumbers[0], 0, &Value);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	printf("Read adc: %d", Value);
}
