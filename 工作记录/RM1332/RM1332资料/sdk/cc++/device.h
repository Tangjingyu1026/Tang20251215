#ifndef __DEVICE_H
#define __DEVICE_H

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

	// 扫描设备
	// 返回值如果大于0，代表获取到设备的个数。如果等于0，代表未插入设备。如果小于0，代表发生错误
	int WINAPI Device_Scan(int* SerialNumbers);
	// 打开设备
	int WINAPI Device_Open(int SerialNumber);
	// 关闭设备
	int WINAPI Device_Close(int SerialNumber);

#if defined(__cplusplus)
}
#endif

#endif
