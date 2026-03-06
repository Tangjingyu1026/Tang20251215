package com.rockmong.rockmong;
import com.sun.jna.ptr.IntByReference;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface PWM extends Library {
	PWM INSTANCE  = (PWM)Native.loadLibrary("rockmong",PWM.class); 
	
	// 初始化PWM
	// SerialNumber: 设备序号
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// Frequency：频率/Hz。最小1Hz, 最大1MHz
	// Duty: 占空比。千分比0~1000
	// Phase: 波形相位。千分比0~1000
	// Polarity: 波形极性。范围0~1。
	// 函数返回：0，正常；<0，异常
	int PWM_Init(int SerialNumber, int Channel, int Frequency, int Duty, int Phase, int Polarity);
	    
	// PWM开始输出
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// RunTimeUs: 输出波形的时间，单位为微妙，启动波形输出之后，RunTimeOfUs微妙之后会停止波形输出，该参数为0，波形会一直输出，直到手动停止，利用该参数可以控制脉冲输出个数。
	// 函数返回：0，正常；<0，异常
	int PWM_Start(int SerialNumber, int Channel, int RunTimeUs);

	// PWM停止输出
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// 函数返回：0，正常；<0，异常
	int PWM_Stop(int SerialNumber, int Channel);

	// PWM占空比动态调节。可以在PWM启动之后调用
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// Duty: 占空比。千分比0~1000
	// 函数返回：0，正常；<0，异常
	int PWM_SetDuty(int SerialNumber, int Channel, int Duty);

	// PWM频率动态调节。可以在PWM启动之后调用
	// Channel: 通道编号。0，PWM0. 1, PWM1 ...
	// Frequency：频率/Hz。最小1Hz, 最大1MHz
	// 函数返回：0，正常；<0，异常
	int PWM_SetFrequency(int SerialNumber, int Channel, int Frequency);
}
