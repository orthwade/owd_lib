#include "c_sleep_for.h"
namespace owd_lib
{
	c_sleep_for_ms::c_sleep_for_ms()
	{
	}
	c_sleep_for_ms::~c_sleep_for_ms()
	{
	}
	void c_sleep_for_ms::operator()(uint64_t milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

	c_sleep_for_mcs::c_sleep_for_mcs()
	{
	}
	c_sleep_for_mcs::~c_sleep_for_mcs()
	{
	}
	void c_sleep_for_mcs::operator()(uint64_t microseconds)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
	}

}