#pragma once
#include <thread>
#include <chrono>

namespace owd_lib
{
	class c_sleep_for_ms
	{
	public:
		c_sleep_for_ms();
		~c_sleep_for_ms();
		void operator()(uint64_t ms = 1);
	};

	class c_sleep_for_mcs
	{
	public:
		c_sleep_for_mcs();
		~c_sleep_for_mcs();
		void operator()(uint64_t mcs = 1);
	};

}


