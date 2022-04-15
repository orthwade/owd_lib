#pragma once
#include <fstream>
#include <string_view>

namespace owd_lib
{
	class c_ifstream
	{
	public:
		c_ifstream();
		~c_ifstream();

		c_ifstream(const c_ifstream& other);
		c_ifstream& operator=(const c_ifstream& other);

		inline std::ifstream& operator()() { return m_ifstream; }

	private:
		std::ifstream m_ifstream{};
	};

	class c_ofstream
	{
	public:
		c_ofstream();
		~c_ofstream();

		c_ofstream(const c_ofstream& other);
		c_ofstream& operator=(const c_ofstream& other);

		inline std::ofstream& operator()() { return m_ofstream; }

	private:
		std::ofstream m_ofstream{};
	};

	class c_wifstream
	{
	public:
		c_wifstream();
		~c_wifstream();

		c_wifstream(const c_wifstream& other);
		c_wifstream& operator=(const c_wifstream& other);

		inline std::wifstream& operator()() { return m_wifstream; }

	private:
		std::wifstream m_wifstream{};
	};

	class c_wofstream
	{
	public:
		c_wofstream();
		~c_wofstream();

		c_wofstream(const c_wofstream& other);
		c_wofstream& operator=(const c_wofstream& other);

		inline std::wofstream& operator()() { return m_wofstream; }

	private:
		std::wofstream m_wofstream{};
	};

}