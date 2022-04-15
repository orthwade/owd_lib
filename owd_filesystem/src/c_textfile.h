#pragma once
#include "c_file.h"

namespace owd_lib
{
	class c_textfile : public c_file
	{
	public:
		c_textfile();

		bool load(std::wstring_view filepath) override;
		bool load(std::wstring_view filepath, std::wstring_view name) override;

		bool save(std::wstring_view filepath) override;

	private:
		std::string m_text{};

	};
}