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

	enum IO_STATE
	{
		IO_STATE_LOW,		//低电平
		IO_STATE_HIGH,		//高电平
	};
	typedef enum IO_STATE IO_STATE_t;

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
	
    //读取引脚状态
    //SerialNumber: 设备序号
    //Pin：引脚编号。0，X0. 1, X1...
    //PinState：返回引脚状态。0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int WINAPI IO_ReadPin(int SerialNumber, int Pin, int *PinState);
	
	//控制引脚输出状态
    //SerialNumber: 设备序号
    //Pin：引脚编号。0，Y0. 1, Y1...
    //PinState：引脚状态。0，继电器断开（晶体管导通）。1，继电器吸合（晶体管断开）
	//函数返回：0，正常；<0，异常
	int WINAPI IO_WritePin(int SerialNumber, int Pin, int PinState);

	int WINAPI IO_ReadMultiPin(int SerialNumber, IO_ReadStruct_Tx_t* TxStruct, IO_ReadStruct_Rx_t* RxStruct, int Number);
	int WINAPI IO_WriteMultiPin(int SerialNumber, IO_WriteStruct_Tx_t* TxStruct, IO_WriteStruct_Rx_t* RxStruct, int Number);

#if defined(__cplusplus)
}
#endif

#endif
