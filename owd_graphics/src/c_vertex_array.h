#pragma once
#include "c_vertex_buffer.h"
#include "c_vertex_buffer_layout.h"

namespace owd_lib
{
	class c_vertex_array
	{
	public:
		c_vertex_array();
		~c_vertex_array();

		c_vertex_array(const c_vertex_array& other);
		c_vertex_array& operator=(const c_vertex_array& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}

		void init();
		void terminate();

		void bind();
		void unbind();

		void add_buffer(c_vertex_buffer& vertex_buffer, c_vertex_buffer_layout& vertex_buffer_layout);
		void set_data(c_vertex_buffer& vertex_buffer, c_vertex_buffer_layout& vertex_buffer_layout);

		void reset();

	private:
		std::wstring m_name{ L"c_vertex_array_object" };

		owd::c_logger m_logger{ L"c_vertex_array", owd::logger_mode_both };

		uint32_t m_ogl_id{};

		uint64_t m_index{};
		uint32_t m_offset{};
	};
}