#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

#if defined(__cplusplus)
extern "C" {
#endif
	
	//初始化ADC
	//SerialNumber: 设备序号
	//Channel：通道编号。0，ADC0. 1, ADC1...
	//SampleRateHz：采样率。一般设置0
	//函数返回：0，正常；<0，异常
	int WINAPI ADC_Init(int SerialNumber, int Channel, int SampleRateHz);
	
	//ADC读取
	//SerialNumber: 设备序号
	//Channel：通道编号。0，ADC0. 1, ADC1...
	//Value：AD值
	//函数返回：0，正常；<0，异常
	int WINAPI ADC_Read(int SerialNumber, int Channel, int *Value);

	struct ADC_Init_TxStruct
	{
		uint8_t Channel;
		uint32_t SampleRateHz;
	};
	typedef struct ADC_Init_TxStruct ADC_Init_TxStruct_t;

	struct ADC_Init_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct ADC_Init_RxStruct ADC_Init_RxStruct_t;

	struct ADC_Read_TxStruct
	{
		uint8_t Channel;
	};
	typedef struct ADC_Read_TxStruct ADC_Read_TxStruct_t;

	struct ADC_Read_RxStruct
	{
		uint8_t Ret;
		uint16_t Value;
	};
	typedef struct ADC_Read_RxStruct ADC_Read_RxStruct_t;

	int WINAPI ADC_InitMulti(int SerialNumber, ADC_Init_TxStruct_t* TxStruct, ADC_Init_RxStruct_t* RxStruct, int Number);
	int WINAPI ADC_ReadMulti(int SerialNumber, ADC_Read_TxStruct_t* TxStruct, ADC_Read_RxStruct_t* RxStruct, int Number);

#if defined(__cplusplus)
}
#endif

#endif
