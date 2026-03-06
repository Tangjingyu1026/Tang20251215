#include "stdio.h"
#include "usb_device.h"
#include "io.h"

#define IO_NUMBER	(16)

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
	
	//P0~P15初始化为输出模式
	IO_InitStruct_Tx_t initStruct_Tx[IO_NUMBER];
	IO_InitStruct_Rx_t initStruct_Rx[IO_NUMBER];
	for (i = 0; i < IO_NUMBER; i++)
	{
		initStruct_Tx[i].Pin = i;
		initStruct_Tx[i].Mode = 1;
		initStruct_Tx[i].Pull = 0;
	}
	ret = IO_InitMultiPin(SerialNumbers[0], initStruct_Tx, initStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0输出低电平
	IO_WriteStruct_Tx_t writeStruct_Tx[IO_NUMBER];
	IO_WriteStruct_Rx_t writeStruct_Rx[IO_NUMBER];
	for (i = 0; i < IO_NUMBER; i++)
	{
		writeStruct_Tx[i].Pin = i;
		writeStruct_Tx[i].PinState = 0;
	}
	ret = IO_WriteMultiPin(SerialNumbers[0], writeStruct_Tx, writeStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0输出高电平
	for (i = 0; i < IO_NUMBER; i++)
	{
		writeStruct_Tx[i].Pin = i;
		writeStruct_Tx[i].PinState = 1;
	}
	ret = IO_WriteMultiPin(SerialNumbers[0], writeStruct_Tx, writeStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0初始化为输入模式
	for (i = 0; i < IO_NUMBER; i++)
	{
		initStruct_Tx[i].Pin = i;
		initStruct_Tx[i].Mode = 0;
		initStruct_Tx[i].Pull = 1;//上拉
	}
	ret = IO_InitMultiPin(SerialNumbers[0], initStruct_Tx, initStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//读取P0状态
	IO_ReadStruct_Tx_t readStruct_Tx[IO_NUMBER];
	IO_ReadStruct_Rx_t readStruct_Rx[IO_NUMBER];
	for (i = 0; i < IO_NUMBER; i++)
	{
		readStruct_Tx[i].Pin = i;
	}
	ret = IO_ReadMultiPin(SerialNumbers[0], readStruct_Tx, readStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	for (i = 0; i < IO_NUMBER; i++)
	{
		printf("Read pin%d: %d\n", i, readStruct_Rx[i].PinState);
	}
	
}
