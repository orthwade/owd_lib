#include "os_specific_sleep.h"
#ifdef __linux__ 

#elif _WIN32
	namespace owd_lib
	{
		static auto set_time_resolution = timeBeginPeriod(1);
	}
#else

#endif
namespace owd_lib
{
void sleep_ms(int32_t ms_count)
{
	#ifdef __linux__ 
		usleep(ms_count * 1000);
	#elif _WIN32
		Sleep(ms_count);
	#else
	#endif
}
}

