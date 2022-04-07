#define _CRT_SECURE_NO_WARNINGS
#include "time_date.h"

namespace owd_lib
{
	
	std::string_view c_time_date::operator()()
	{
		//time_t ltime;
		//wchar_t buf[26];
		//errno_t err;

		//time(&ltime);
		//err = _wctime_s(buf, 26, &ltime);
		//std::string wstr(buf);
		//m_time_date_str = std::string(wstr.begin(), wstr.end());

		using std::chrono::system_clock;

		system_clock::time_point tp = system_clock::now();

		time_t raw_time = system_clock::to_time_t(tp);

		struct tm* timeinfo = std::localtime(&raw_time);
		char buf[24] = { 0 };
		strftime(buf, 24, "%Y-%m-%d %H:%M:%S.", timeinfo);

		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());

		std::string milliseconds_str = std::to_string(ms.count() % 1000);

		if (milliseconds_str.length() < 3) {
			milliseconds_str = '0' + milliseconds_str;
		}
		m_time_date_str.clear();
		m_time_date_str.append(buf);
		m_time_date_str.append(milliseconds_str);
		//m_time_date_str = std::string(buf) + milliseconds_str;

		return m_time_date_str;
	}
	std::string c_time_date::time_date()
	{
		update();
		return m_time_date_str;
	}
	std::string c_time_date::time()
	{
		update();
		return m_time_str;
	}
	std::string c_time_date::time_ms()
	{
		update();
		return m_time_ms_str;
	}
	std::string c_time_date::date()
	{
		update();
		return m_date_str;
	}
	std::string_view c_time_date::time_view()
	{
		using std::chrono::system_clock;

		system_clock::time_point tp = system_clock::now();

		time_t raw_time = system_clock::to_time_t(tp);

		struct tm* timeinfo = std::localtime(&raw_time);
		char buf[24] = { 0 };
		strftime(buf, 24, "%Y-%m-%d %H:%M:%S.", timeinfo);

		m_time_str.clear();
		m_time_str.resize(8);

		m_time_str.at(0) = buf[11 + 0];
		m_time_str.at(1) = buf[11 + 1];
		m_time_str.at(2) = buf[11 + 2];
		m_time_str.at(3) = buf[11 + 3];
		m_time_str.at(4) = buf[11 + 4];
		m_time_str.at(5) = buf[11 + 5];
		m_time_str.at(6) = buf[11 + 6];
		m_time_str.at(7) = buf[11 + 7];

		//m_time_str.append(buf);
		//m_time_str = std::string(buf) + milliseconds_str;

		return m_time_str;
	}
	std::string_view c_time_date::time_ms_view()
	{
		using std::chrono::system_clock;

		system_clock::time_point tp = system_clock::now();

		time_t raw_time = system_clock::to_time_t(tp);

		struct tm* timeinfo = std::localtime(&raw_time);
		char buf[24] = { 0 };
		strftime(buf, 24, "%Y-%m-%d %H:%M:%S.", timeinfo);

		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());

		std::string milliseconds_str = std::to_string(ms.count() % 1000);

		if (milliseconds_str.length() < 2) {
			milliseconds_str = "00" + milliseconds_str;
		}

		if (milliseconds_str.length() < 3) {
			milliseconds_str = '0' + milliseconds_str;
		}
		m_time_ms_str.clear();
		m_time_ms_str.resize(12);
		char* buf_ptr = buf;
		buf_ptr += 11;
		char* str_ptr = m_time_ms_str.data();

		memcpy(str_ptr, buf_ptr, 9);
		//str_ptr = m_time_ms_str.data(); 
		str_ptr += 9;
		memcpy(str_ptr, milliseconds_str.c_str(), 3);

		//m_time_ms_str = std::string(buf) + milliseconds_str;

		return m_time_ms_str;
	}
	std::string_view c_time_date::date_view()
	{
		using std::chrono::system_clock;


		system_clock::time_point tp = system_clock::now();

		time_t raw_time = system_clock::to_time_t(tp);

		struct tm* timeinfo = std::localtime(&raw_time);
		char buf[24] = { 0 };
		strftime(buf, 24, "%Y-%m-%d %H:%M:%S.", timeinfo);
		m_date_str.clear();
		m_date_str.resize(10);

		auto ptr = m_date_str.data();
		memcpy(ptr, buf, 10);
		//m_date_str.append(buf);

		//m_date_str.append(milliseconds_str);
		//m_date_str = std::string(buf) + milliseconds_str;

		return m_date_str;
	}
	void c_time_date::update()
	{
		using std::chrono::system_clock;

		system_clock::time_point tp = system_clock::now();

		time_t raw_time = system_clock::to_time_t(tp);

		struct tm* timeinfo = std::localtime(&raw_time);
		char buf[24] = { 0 };
		strftime(buf, 24, "%Y-%m-%d %H:%M:%S.", timeinfo);

		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());

		std::string milliseconds_str = std::to_string(ms.count() % 1000);

		if (milliseconds_str.length() < 3) {
			milliseconds_str = '0' + milliseconds_str;
		}
		m_time_date_str.clear();
		m_time_date_str.append(buf);
		m_time_date_str.append(milliseconds_str);
	}
}