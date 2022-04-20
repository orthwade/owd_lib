#pragma once
#include "opengl/opengl.h"

namespace owd_lib
{
	class c_index_buffer
	{
	public:
		c_index_buffer();
		~c_index_buffer();

		c_index_buffer(const c_index_buffer& other);
		c_index_buffer& operator=(const c_index_buffer& other);

		void set_name(std::wstring_view name);

		std::wstring_view name()
		{
			return m_name;
		}

		void init();
		void terminate();

		//void set_vertex_positions(std::vector<float>& input);

		void set(const std::vector<uint32_t>& indices);
		void add(const std::vector<uint32_t>& indices);
		void add(const std::vector<uint32_t>& indices, bool update_buffer_data_);

		void update_buffer_data();

		void bind();
		void unbind();
		inline std::vector<uint32_t>& indices() { return m_indices; }
		inline size_t count() { return m_indices.size(); }

		gl_index_t max_index();

	private:
		std::wstring m_name{ L"c_index_buffer_object" };

		owd::c_logger m_logger{ L"c_index_buffer", owd::logger_mode_both };

		//uint32_t m_ogl_buf_id{};
		uint32_t m_ogl_buffer_id{};

		//std::vector<float> m_vertex_positions
		//{
		//	-0.5f, -0.5f,
		//	0.5f, -0.5f,
		//	 0.5f, 0.5f,
		//	 -0.5f, 0.5f
		//};

		/*std::vector<uint32_t> m_indices
		{
			0, 1, 2,
			2, 3, 0
		};*/

		std::vector<uint32_t> m_indices{};
	};
}