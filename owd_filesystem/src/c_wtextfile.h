#pragma once
#include "c_file.h"

namespace owd_lib
{
	class c_wtextfile : public c_file
	{
	public:
		c_wtextfile();

		bool load(std::wstring_view filepath) override;
		bool load(std::wstring_view filepath, std::wstring_view name) override;

		bool save(std::wstring_view filepath) override;

	private:
		std::wstring m_text{};
		c_wifstream m_wifstream{};
		c_wofstream m_wofstream{};
	};
}