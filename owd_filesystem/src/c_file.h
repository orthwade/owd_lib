#pragma once

#include <owd_misc.h>
#include <owd_strings.h>

#include "filestream.h"

namespace owd_lib
{
	class c_file : public owd::c_basic_object
	{
	public:
		enum class enm_state
		{
			not_loaded,
			good,
			error
		};

		c_file();

		virtual bool load(std::wstring_view filepath);
		virtual bool load(std::wstring_view filepath, std::wstring_view name);

		virtual bool save(std::wstring_view filepath);

		virtual void reset() override;

		inline std::wstring_view filepath() const { return m_filepath; }

		inline enm_state state() const { return m_state; }

		bool good() const override;
		std::wstring_view filepath();
	protected:
		enm_state		m_state = enm_state::not_loaded;

		std::wstring	m_extension{ L"owd_file" };
		std::wstring	m_filepath{};

		c_ifstream	m_ifstream{};

		c_ofstream	m_ofstream{};

		bool load_default(std::wstring_view filepath);
		bool load_default(std::wstring_view filepath, std::wstring_view name);
		bool save_default(std::wstring_view filepath);
	};
}