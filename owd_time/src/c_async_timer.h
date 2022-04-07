#pragma once
#include <atomic>
#include "misc_defines.h"

namespace owd_lib
{
		
	class c_async_timer
	{
		enum class enm_state
		{
			waiting,
			done
		};
	public:
		c_async_timer();
		c_async_timer(uint64_t period_mcs);

		~c_async_timer();
		void init();
		void init(uint64_t period_mcs);

		void terminate();

		void start(uint64_t period_mcs);
		void start();

		void wait();

		void stop();

		void set_period(uint64_t period_mcs);

	private:
		std::atomic<enm_state> m_state = enm_state::done;

		std::atomic_bool m_thread_exists = true;

		c_thread m_thread{};

		std::atomic<uint64_t> m_period_mcs{};

		std::chrono::steady_clock::time_point m_frame_start_time{};

		std::chrono::steady_clock::time_point m_frame_end_time{};

		uint64_t m_frame_duration_int_mcs{};

		void do_();
	};
}