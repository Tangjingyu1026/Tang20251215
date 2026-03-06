package com.rockmong.rockmong;
import com.sun.jna.ptr.IntByReference;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface IO extends Library {
	IO INSTANCE  = (IO)Native.loadLibrary("rockmong",IO.class); 
	
    //初始化引脚工作模式
    //SerialNumber: 设备序号
    //Pin：引脚编号。	
	//		通用控制：0，P0. 1, P1...
	//		隔离控制：输入输出方向固定，无需调用此函数
    //Mode：输入输出模式。0，输入。1，输出。2，开漏
    //Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
	//函数返回：0，正常；<0，异常
	int IO_InitPin(int SerialNumber, int Pin, int Mode, int Pull);
	
    //读取引脚状态
    //SerialNumber: 设备序号
    //Pin：引脚编号。
	//		通用控制：0，P0. 1, P1...
	//		隔离控制：0，IN0. 1, IN1...
    //PinState：返回引脚状态。0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int IO_ReadPin(int SerialNumber, int Pin, IntByReference PinState);
	
    //控制引脚输出状态
    //SerialNumber: 设备序号
    //Pin：引脚编号。
	//		通用控制：0，P0. 1, P1...
	//		隔离控制：0，OUT0. 1, OUT1...
    //PinState：引脚状态。0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int IO_WritePin(int SerialNumber, int Pin, int PinState);
	
    //读取输出引脚状态
    //SerialNumber: 设备序号
    //Pin：引脚编号。
	//		通用控制：0，P0. 1, P1...
	//		隔离控制：0，OUT0. 1, OUT1...
    //PinState：返回引脚状态。0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int IO_ReadOutputPin(int SerialNumber, int Pin, IntByReference PinState);
	
	// ------------------ 以下是隔离控制常用接口 ------------------
	
	//同时控制所有引脚输出状态（最多32路）
	//SerialNumber: 设备序号
	//PinState：写入引脚状态。每一个bit代表一个IO。如bit0为OUT0, bit1为OUT1，以此类推
	//    相应bit为0，继电器断开（晶体管导通）。1，继电器吸合（晶体管断开）
	//函数返回：0，正常；<0，异常
	int IO_WritePin_Bit(int SerialNumber, int PinState);

	//同时读取所有输出引脚状态（最多32路）
	//SerialNumber: 设备序号
	//PinState：返回引脚状态。每一个bit代表一个IO。如bit0为OUT0, bit1为OUT1，以此类推
	//    相应bit为0，继电器断开（晶体管导通）。1，继电器吸合（晶体管断开）
	//函数返回：0，正常；<0，异常
	int IO_ReadOutputPin_Bit(int SerialNumber, IntByReference PinState);

	//同时读取所有输入引脚状态（最多32路）
	//SerialNumber: 设备序号
	//PinState：返回引脚状态。每一个bit代表一个IO。如bit0为IN0, bit1为IN1，以此类推
	//    相应bit为0，低电平。1，高电平
	//函数返回：0，正常；<0，异常
	int IO_ReadPin_Bit(int SerialNumber, IntByReference PinState);
}
