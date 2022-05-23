#pragma once
#ifndef OS_SPECIFIC_SLEEP
	#ifdef __linux__ 
		#include <unistd.h>
	#elif _WIN32
		#include <windows.h>
	#else
	#endif
	#define OS_SPECIFIC_SLEEP
#endif

#include <stdint.h>

namespace owd_lib
{
	void sleep_ms(int32_t ms_count);
}

