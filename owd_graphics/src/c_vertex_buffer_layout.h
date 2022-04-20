#pragma once
#include "c_vertex_buffer_element.h"

namespace owd_lib
{
	class c_vertex_buffer_layout
	{
	public:
		c_vertex_buffer_layout();
		~c_vertex_buffer_layout();

		c_vertex_buffer_layout(const c_vertex_buffer_layout& other);
		c_vertex_buffer_layout& operator=(const c_vertex_buffer_layout& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}

		inline void add_element(uint32_t count, uint32_t type = GL_FLOAT, bool normalized = false)
		{
			//m_mtx.lock();
			{
				m_elements.push_back({ type, count, normalized });
				m_stride += count * c_vertex_buffer_element::ogl_type_size_bytes(type);
			}
			//m_mtx.unlock();
		}

		inline std::vector<c_vertex_buffer_element> elements()
		{
			return m_elements;
		}

		inline uint32_t stride()
		{
			return m_stride;
		}

		inline void clear()
		{
			m_elements.clear();
			m_stride = 0;
		}

	private:
		std::wstring m_name{ L"c_vertex_buffer_layout_object" };
		owd::c_logger m_logger{ L"c_vertex_buffer_layout", owd::logger_mode_both };

		uint32_t m_stride{};
		std::vector<c_vertex_buffer_element> m_elements{};
	};
}