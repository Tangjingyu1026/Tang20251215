#include "stdio.h"
#include "usb_device.h"
#include "io.h"
#include "adc.h"

#define ADC_NUM		(8)

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
	
	//初始化ADC
	ADC_Init_TxStruct_t ADC_Init_TxStruct[ADC_NUM];
	ADC_Init_RxStruct_t ADC_Init_RxStruct[ADC_NUM];
	for (i = 0; i < ADC_NUM; i++)
	{
		ADC_Init_TxStruct[i].Channel = i;
		ADC_Init_TxStruct[i].SampleRateHz = 0;
	}
	ret = ADC_InitMulti(SerialNumbers[0], ADC_Init_TxStruct, ADC_Init_TxStruct, ADC_NUM);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//读取ADC
	ADC_Read_TxStruct_t ADC_Read_TxStruct[ADC_NUM];
	ADC_Read_RxStruct_t ADC_Read_RxStruct[ADC_NUM];
	for (i = 0; i < ADC_NUM; i++)
	{
		ADC_Read_TxStruct[i].Channel = i;
	}
	ret = ADC_ReadMulti(SerialNumbers[0], ADC_Read_TxStruct, ADC_Read_RxStruct, ADC_NUM);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	else
	{
		for (i = 0; i < ADC_NUM; i++)
		{
			printf("adc[%d]: %d\n", i, ADC_Read_RxStruct[i].Value);
		}		
	}
	
}
