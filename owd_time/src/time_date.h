#pragma once
#include <string_view>
#include <chrono>
#include <time.h>
#include <string>

namespace owd_lib
{
	class c_time_date
	{
	public:
		std::string_view operator()();

		std::string time_date();
		std::string time();
		std::string time_ms();
		std::string date();

		std::string_view time_view();
		std::string_view time_ms_view();
		std::string_view date_view();
	private:
		std::string m_time_date_str{};
		std::string m_time_str{};
		std::string m_time_ms_str{};
		std::string m_date_str{};

		void update();
	};
}



