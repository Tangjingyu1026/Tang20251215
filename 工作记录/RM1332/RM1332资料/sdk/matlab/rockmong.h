#ifndef __USB_DEVICE_H
#define __USB_DEVICE_H

#include "stdint.h"
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

	// --------- IO ---------
	struct IO_InitStruct_Tx
	{
		uint8_t Pin;
		uint8_t Mode;
		uint8_t Pull;
	};
	typedef struct IO_InitStruct_Tx IO_InitStruct_Tx_t;

	struct IO_InitStruct_Rx
	{
		uint8_t Ret;
	};
	typedef struct IO_InitStruct_Rx IO_InitStruct_Rx_t;

	struct IO_ReadStruct_Tx
	{
		uint8_t Pin;
	};
	typedef struct IO_ReadStruct_Tx IO_ReadStruct_Tx_t;

	struct IO_ReadStruct_Rx
	{
		uint8_t Ret;
		uint8_t PinState;
	};
	typedef struct IO_ReadStruct_Rx IO_ReadStruct_Rx_t;

	struct IO_WriteStruct_Tx
	{
		uint8_t Pin;
		uint8_t PinState;
	};
	typedef struct IO_WriteStruct_Tx IO_WriteStruct_Tx_t;
	
	struct IO_WriteStruct_Rx
	{
		uint8_t Ret;
	};
	typedef struct IO_WriteStruct_Rx IO_WriteStruct_Rx_t;
	
	//扫描USB设备
	//返回值如果大于0，代表获取到设备的个数。如果等于0，代表未插入设备。如果小于0，代表发生错误
	int WINAPI UsbDevice_Scan(int* SerialNumbers);
	
	//初始化引脚工作模式
	//SerialNumber: 设备序号
	//Pin：引脚编号。0，P0. 1, P1...
	//Mode：输入输出模式。0，输入。1，输出。2，开漏
	//Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
	//函数返回：0，正常；<0，异常
	int WINAPI IO_InitPin(int SerialNumber, int Pin, int Mode, int Pull);
	
	//读取引脚状态
	//SerialNumber: 设备序号
	//Pin：引脚编号。0，P0. 1, P1...
	//PinState：返回引脚状态。0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int WINAPI IO_ReadPin(int SerialNumber, int Pin, int *PinState);
	
	//控制引脚输出状态
	//SerialNumber: 设备序号
	//Pin：引脚编号。0，P0. 1, P1...
	//PinState：引脚状态。0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int WINAPI IO_WritePin(int SerialNumber, int Pin, int PinState);

	//int WINAPI IO_InitMultiPin(int SerialNumber, IO_InitStruct_Tx_t* TxStruct, IO_InitStruct_Rx_t* RxStruct, int Number);
	int WINAPI IO_InitMultiPin(int SerialNumber, struct IO_InitStruct_Tx* TxStruct, struct IO_InitStruct_Rx* RxStruct, int Number);
	int WINAPI IO_ReadMultiPin(int SerialNumber, IO_ReadStruct_Tx_t* TxStruct, IO_ReadStruct_Rx_t* RxStruct, int Number);
	int WINAPI IO_WriteMultiPin(int SerialNumber, IO_WriteStruct_Tx_t* TxStruct, IO_WriteStruct_Rx_t* RxStruct, int Number);
	
	int WINAPI SPI_Init(int SerialNumber, int Channel, int Mode, int CPOL, int CPHA, int NSS, int BaudRate);
	int WINAPI SPI_WriteBytes(int SerialNumber, int Channel, uint8_t *Bytes, int Length);
	int WINAPI SPI_ReadBytes(int SerialNumber, int Channel, uint8_t *Bytes, int Length);
	int WINAPI SPI_WriteReadBytes(int SerialNumber, int Channel, uint8_t *WriteBytes, int WriteLength, uint8_t *ReadBytes, int ReadLength);
		
	// --------- PWM ---------
	struct PWM_Init_TxStruct
	{
		uint8_t Channel;
		uint32_t Frequency;	// 频率Hz
		uint16_t Duty;		// 占空比。千分比
		uint16_t Phase;		// 相位。千分比
		uint8_t Polarity;	// 波形极性，取值0或者1
	};
	typedef struct PWM_Init_TxStruct PWM_Init_TxStruct_t;

	struct PWM_Init_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_Init_RxStruct PWM_Init_RxStruct_t;

	struct PWM_Start_TxStruct
	{
		uint8_t Channel;
		uint32_t RunTimeUs;
	};
	typedef struct PWM_Start_TxStruct PWM_Start_TxStruct_t;

	struct PWM_Start_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_Start_RxStruct PWM_Start_RxStruct_t;

	struct PWM_Stop_TxStruct
	{
		uint8_t Channel;
	};
	typedef struct PWM_Stop_TxStruct PWM_Stop_TxStruct_t;

	struct PWM_Stop_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_Stop_RxStruct PWM_Stop_RxStruct_t;

	struct PWM_SetDuty_TxStruct
	{
		uint8_t Channel;
		uint16_t Duty;
	};
	typedef struct PWM_SetDuty_TxStruct PWM_SetDuty_TxStruct_t;

	struct PWM_SetDuty_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_SetDuty_RxStruct PWM_SetDuty_RxStruct_t;

	struct PWM_SetPhase_TxStruct
	{
		uint8_t Channel;
		uint16_t Phase;
	};
	typedef struct PWM_SetPhase_TxStruct PWM_SetPhase_TxStruct_t;

	struct PWM_SetPhase_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_SetPhase_RxStruct PWM_SetPhase_RxStruct_t;

	struct PWM_SetFrequency_TxStruct
	{
		uint8_t Channel;
		uint32_t Frequency;	// 频率Hz
	};
	typedef struct PWM_SetFrequency_TxStruct PWM_SetFrequency_TxStruct_t;

	struct PWM_SetFrequency_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_SetFrequency_RxStruct PWM_SetFrequency_RxStruct_t;

	struct PWM_Start_withList_TxStruct
	{
		uint8_t Channel;
		uint32_t Frequency;	// 频率Hz
		uint16_t Duty;
		uint16_t WaveCount;
	};
	typedef struct PWM_Start_withList_TxStruct PWM_Start_withList_TxStruct_t;

	struct PWM_Start_withList_RxStruct
	{
		uint8_t Ret;
	};
	typedef struct PWM_Start_withList_RxStruct PWM_Start_withList_RxStruct_t;
	
	// 初始化PWM
	// SerialNumber: 设备序号
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// Frequency：频率/Hz。最小1Hz, 最大1MHz
	// Duty: 占空比。千分比0~1000
	// Phase: 波形相位。范围0~1000。
	// Polarity: 波形极性。范围0~1。
	// 函数返回：0，正常；<0，异常
	int WINAPI PWM_Init(int SerialNumber, int Channel, int Frequency, int Duty, int Phase, int Polarity);
	
	// PWM开始输出
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// RunTimeUs: 输出波形的时间，单位为微妙，启动波形输出之后，RunTimeOfUs微妙之后会停止波形输出，该参数为0，波形会一直输出，直到手动停止，利用该参数可以控制脉冲输出个数。
	// 函数返回：0，正常；<0，异常
	int WINAPI PWM_Start(int SerialNumber, int Channel, int RunTimeUs);

	// PWM停止输出
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// 函数返回：0，正常；<0，异常
	int WINAPI PWM_Stop(int SerialNumber, int Channel);

	// PWM占空比动态调节。可以在PWM启动之后调用
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// Duty: 占空比。千分比0~1000
	// 函数返回：0，正常；<0，异常
	int WINAPI PWM_SetDuty(int SerialNumber, int Channel, int Duty);

	// PWM频率动态调节。可以在PWM启动之后调用
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// Frequency：频率/Hz。最小1Hz, 最大1MHz
	// 函数返回：0，正常；<0，异常
	int WINAPI PWM_SetFrequency(int SerialNumber, int Channel, int Frequency);	
	
	int WINAPI PWM_InitMulti(int SerialNumber, PWM_Init_TxStruct_t* TxStruct, PWM_Init_RxStruct_t* RxStruct, int Number);
	int WINAPI PWM_StartMulti(int SerialNumber, PWM_Start_TxStruct_t* TxStruct, PWM_Start_RxStruct_t* RxStruct, int Number);
	int WINAPI PWM_StopMulti(int SerialNumber, PWM_Stop_TxStruct_t* TxStruct, PWM_Stop_RxStruct_t* RxStruct, int Number);
	int WINAPI PWM_SetDutyMulti(int SerialNumber, PWM_SetDuty_TxStruct_t* TxStruct, PWM_SetDuty_RxStruct_t* RxStruct, int Number);
	int WINAPI PWM_SetPhaseMulti(int SerialNumber, PWM_SetPhase_TxStruct_t* TxStruct, PWM_SetPhase_RxStruct_t* RxStruct, int Number);
	int WINAPI PWM_SetFrequencyMulti(int SerialNumber, PWM_SetFrequency_TxStruct_t* TxStruct, PWM_SetFrequency_RxStruct_t* RxStruct, int Number);

	int WINAPI PWM_Start_withList(int SerialNumber, PWM_Start_withList_TxStruct_t* TxStruct, PWM_Start_withList_RxStruct_t* RxStruct, int Number);
#if defined(__cplusplus)
}
#endif

#endif
