#pragma once
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "Winmm.lib")
#else
#include <>
#endif // _WIN32

namespace owd_lib
{
	class c_async_timer_lib
	{
		enum class enm_state
		{
			waiting,
			done
		};
	public:
		c_async_timer_lib();
		c_async_timer_lib(uint64_t period_mcs);

		~c_async_timer_lib();
		void init();
		void init(uint64_t period_ms);

		void terminate();

		void start(uint64_t period_ms);
		void start();

		void wait();

		void stop();

		void set_period(uint64_t period_ms);

	private:
		std::atomic<enm_state> m_state = enm_state::done;

		std::atomic_bool m_thread_exists = true;

		std::thread m_thread{};

		std::atomic<uint64_t> m_period_ms{};
		std::mutex m_mtx{};
		std::condition_variable m_conditional{};

		//std::chrono::steady_clock::time_point m_frame_start_time{};

		//std::chrono::steady_clock::time_point m_frame_end_time{};

		uint64_t m_frame_duration_int_ms{};
		void do_();
		void sleep_(uint64_t ms);

	};
}