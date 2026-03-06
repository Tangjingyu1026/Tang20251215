#ifndef __USB_DEVICE_H
#define __USB_DEVICE_H

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

	//扫描USB设备
	//返回值如果大于0，代表获取到设备的个数。如果等于0，代表未插入设备。如果小于0，代表发生错误
	int WINAPI UsbDevice_Scan(int* SerialNumbers);

#if defined(__cplusplus)
}
#endif

#endif
