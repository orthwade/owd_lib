#pragma once
#include <list>
#include <mutex>
#include <condition_variable>
#include "c_texture.h"

namespace owd_lib
{
	class c_texture_bank : public owd::c_file_bank<c_texture>
	{
		struct s_buffer
		{
			std::wstring filepath{};
			std::wstring name{};
		};
	public:
		static c_texture_bank* get_instance();
		static void terminate();

		bool load(std::wstring_view filepath, std::wstring_view name);
		bool erase(std::wstring_view name);
		texture_t& get(std::wstring_view name);
		void update_main_thread();

	private:
		static c_texture_bank* m_singleton;

		std::mutex m_mtx{};
		std::condition_variable m_conditional_variable{};
		std::atomic_bool m_should_update{ false };
		std::list<s_buffer> m_list_buffer{};
		std::list<std::wstring> m_list_erase{};

		void wait_update();

		c_texture_bank();
		~c_texture_bank();

		c_texture_bank(const c_texture_bank&) = delete;
		c_texture_bank& operator=(const c_texture_bank&) = delete;
	};
}