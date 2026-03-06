#include "stdio.h"
#include "usb_device.h"
#include "io.h"

int main(int argc, char *argv[])
{
	int ret = 0, i;
	int SerialNumbers[16];
	int PinState = 0;
	int pin, rw, state;
	int need_help = 0;
	int sn;
	
	if (argc == 3)
	{
		rw = atoi(argv[1]);
		pin = atoi(argv[2]);
		if (rw != 0)
		{
			need_help = 1;
		}
	}
	else if (argc == 4)
	{
		rw = atoi(argv[1]);
		pin = atoi(argv[2]);
		if (rw != 1)
		{
			need_help = 1;
		}
		else
		{
			state = atoi(argv[3]);
			state = state == 0 ? 0 : 1;
		}		
	}
	else
	{
		need_help = 1;
	}

	if (need_help)
	{
		printf("The first argument is read or write, which is 0 for read and 1 for write.\n");
		printf("The second argument is the pin number, which ranges from 0 to 15.\n");
		printf("When writing, the third argument is the high or low level to be written. 0 is low and 1 is high.\n");
		printf("Example:\n");
		printf("\t Read P0: 0 0\n");
		printf("\t Read P15: 0 15\n");
		printf("\t Write P0 high: 1 0 1\n");
		printf("\t Write P0 low: 1 0 0\n");
		printf("\t Write P15 high: 1 15 1\n");
		printf("\t Write P15 low: 1 15 0\n");
		return;
	}
	
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

	sn = SerialNumbers[0];
	
	//初始化
	ret = IO_InitPin(sn, pin, rw, 0);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	if (0 == rw)
	{
		//读取状态
		ret = IO_ReadPin(sn, pin, &PinState);
		if (ret < 0)
		{
			printf("Error: %d\n", ret);
			return ret;
		}
		printf("Read P%d: %d", pin, PinState);
	}
	else
	{
		//输出电平
		ret = IO_WritePin(sn, pin, state);
		if (ret < 0)
		{
			printf("Error: %d\n", ret);
			return ret;
		}
		printf("Write P%d: %d", pin, state);
	}
	printf("\n");
}
