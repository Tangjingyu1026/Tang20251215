#ifndef __IO_H
#define __IO_H

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

	enum IO_MODE
	{
		IO_MODE_INPUT,			//输入模式
		IO_MODE_OUTPUT,			//输出模式
		IO_MODE_OPEN_DRAIN,		//开漏模式
	};
	typedef enum IO_MODE IO_MODE_t;

	enum IO_PULL
	{
		IO_NOPULL,			//没有上拉下拉
		IO_PULLUP,			//上拉
		IO_PULLDOWN,		//下拉
	};
	typedef enum IO_PULL IO_PULL_t;

	enum IO_STATE
	{
		IO_STATE_LOW,		//低电平
		IO_STATE_HIGH,		//高电平
	};
	typedef enum IO_STATE IO_STATE_t;

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

	int WINAPI IO_InitMultiPin(int SerialNumber, IO_InitStruct_Tx_t* TxStruct, IO_InitStruct_Rx_t* RxStruct, int Number);
	int WINAPI IO_ReadMultiPin(int SerialNumber, IO_ReadStruct_Tx_t* TxStruct, IO_ReadStruct_Rx_t* RxStruct, int Number);
	int WINAPI IO_WriteMultiPin(int SerialNumber, IO_WriteStruct_Tx_t* TxStruct, IO_WriteStruct_Rx_t* RxStruct, int Number);

#if defined(__cplusplus)
}
#endif

#endif
