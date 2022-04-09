#include "owd_debug.h"
#include "../src/logger.h"

static owd_lib::c_logger_lib* lib_logger(void* data)
{
	return reinterpret_cast<owd_lib::c_logger_lib*>(data);
}

owd::c_logger::c_logger()
	: 
	m_name(L"logger"),
	m_data(new owd_lib::c_logger_lib(m_name, owd_lib::enm_log_mode::both))
{
}

owd::c_logger::c_logger(std::wstring_view name)
	:
	m_name(name),
	m_data(new owd_lib::c_logger_lib(m_name, owd_lib::enm_log_mode::both))
{
}

owd::c_logger::c_logger(std::wstring_view name, uint16_t mode)
	:
	m_name(name),
	m_data(new owd_lib::c_logger_lib(m_name, owd_lib::enm_log_mode::both))
{
	set_mode(mode);
}

owd::c_logger::~c_logger()
{
	delete lib_logger(m_data);
}

namespace owd
{
	void c_logger::set_mode(uint16_t mode)
	{
		switch (mode)
		{
		case 0:
			lib_logger(m_data)->set_mode(owd_lib::enm_log_mode::none);
			break;
		case 1:
			lib_logger(m_data)->set_mode(owd_lib::enm_log_mode::console);
			break;
		case 2:
			lib_logger(m_data)->set_mode(owd_lib::enm_log_mode::file);
			break;
		case 3:
			lib_logger(m_data)->set_mode(owd_lib::enm_log_mode::both);
			break;
		default:
			break;
		}
	}
	void c_logger::enable_global_mode_override()
	{
		owd_lib::c_logger_lib::enable_global_mode_override();
	}
	void c_logger::disable_global_mode_override()
	{
		owd_lib::c_logger_lib::disable_global_mode_override();
	}
	void c_logger::set_global_mode_override(uint16_t mode)
	{
		switch (mode)
		{
		case 0:
			owd_lib::c_logger_lib::set_global_mode_override(owd_lib::enm_log_mode::none);
			break;
		case 1:
			owd_lib::c_logger_lib::set_global_mode_override(owd_lib::enm_log_mode::console);
			break;
		case 2:
			owd_lib::c_logger_lib::set_global_mode_override(owd_lib::enm_log_mode::file);
			break;
		case 3:
			owd_lib::c_logger_lib::set_global_mode_override(owd_lib::enm_log_mode::both);
			break;
		default:
			break;
		}
	}
	c_logger& owd::c_logger::operator<<(uint8_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& owd::c_logger::operator<<(uint16_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(uint32_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(uint64_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(int8_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(int16_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(int32_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(int64_t input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(float input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(double input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(const char* input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(std::string_view input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(std::wstring_view input)
	{
		(*lib_logger(m_data)) << input;
		return *this;
	}
	c_logger& c_logger::operator<<(char c)
	{
		(*lib_logger(m_data)) << c;
		return *this;
	}
	c_logger& c_logger::operator<<(wchar_t c)
	{
		(*lib_logger(m_data)) << c;
		return *this;
	}
}