#pragma once
#include "opengl/opengl.h"


namespace owd_lib
{
	class c_vertex_buffer_element
	{
	public:
		c_vertex_buffer_element();
		c_vertex_buffer_element(uint32_t type, uint32_t count, bool normalized);
		~c_vertex_buffer_element();

		c_vertex_buffer_element(const c_vertex_buffer_element& other);
		c_vertex_buffer_element& operator=(const c_vertex_buffer_element& other);

		uint32_t	m_type{};
		uint32_t	m_count{};
		bool		m_normalized{};

		std::wstring_view ogl_type_str();

		static std::wstring_view ogl_type_str(uint32_t type);


		uint32_t ogl_type_size_bytes();
		static uint32_t ogl_type_size_bytes(uint32_t type);

	private:
	};
}