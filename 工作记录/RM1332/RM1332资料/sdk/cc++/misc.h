#ifndef __MISC_H
#define __MISC_H

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

	int WINAPI MISC_GetFwVersion(int SerialNumber, char* Ver);
	int WINAPI MISC_GetModel(int SerialNumber, char* Model);
	int WINAPI MISC_GetLibraryVersion(char* Ver);

#if defined(__cplusplus)
}
#endif

#endif
