#pragma once
#include <string_view>

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#else
#include <>
#endif // _WIN32

namespace owd
{
	std::string time_date();
	std::string time();
	std::string time_ms();
	std::string date();
	void sleep_for_ms(size_t count);

	class c_async_timer
	{
	public:
		void start(size_t period_mcs);
		void wait();
		void stop();
		void terminate();

		c_async_timer();
		~c_async_timer();
	private:
		void* m_data;
	};

	class c_frame_timer
	{
	public:
		static c_frame_timer* get_instance();
		static void terminate();

		void wait_frame();

		void set_fps(float fps);

	private:
		static c_frame_timer* m_singleton;
	};

}