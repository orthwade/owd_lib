#pragma once
#include <array>

#include <owd_filesystem.h>

#include "c_colour_uniform.h"

namespace owd_lib
{
	struct s_shader
	{
		s_shader(uint32_t gl_code, std::string_view start_delimiter, std::string_view end_delimiter)
			:
			m_gl_code(gl_code),
			m_start_delimiter(start_delimiter),
			m_end_delimiter(end_delimiter),
			m_string()
		{

		}

		s_shader(const s_shader& other)
		{
			*this = other;
		}
		s_shader& operator=(const s_shader& other)
		{
			if (this != &other)
			{
				m_gl_code			= other.m_gl_code;
				m_gl_shader_id		= other.m_gl_shader_id	;
				m_start_delimiter	= other.m_start_delimiter;
				m_end_delimiter		= other.m_end_delimiter;
				m_string			= other.m_string;
			}
			return *this;
		}

		uint32_t    m_gl_code{};
		uint32_t    m_gl_shader_id{};
		std::string m_start_delimiter{};
		std::string m_end_delimiter{};
		std::string m_string{};
		bool m_enabled = false;
	};
}

namespace owd_lib
{
	class c_shader : public owd::c_textfile
	{
	public:
		c_shader();
		c_shader(std::wstring_view filepath);
		~c_shader();

		bool load(std::wstring_view filepath) override;
		bool load(std::wstring_view filepath, std::wstring_view name) override;

		void init();
		void terminate();

		void bind();
		static void unbind();
		uint32_t shader_program_id();

		inline std::wstring_view filepath()
		{
			return m_filepath;
		}

	private:
		uint32_t m_shader_program_id{};

		uint32_t m_ogl_vs_id{};
		uint32_t m_ogl_fs_id{};

		std::array<s_shader, 6> m_array_gl_shader_struct
		{
			s_shader{ GL_COMPUTE_SHADER, "\/\/----start_gl_compute_shader----", "\/\/----end_gl_compute_shader----" },

			s_shader{GL_VERTEX_SHADER, "\/\/----start_gl_vertex_shader----", "\/\/----end_gl_vertex_shader----"},

			s_shader
			{GL_TESS_CONTROL_SHADER, "\/\/----start_gl_tess_control_shader----", "\/\/----end_gl_tess_control_shader----"},

			s_shader{GL_TESS_EVALUATION_SHADER, "\/\/----start_gl_tess_evaluation_shader----",
			"\/\/----end_gl_tess_evaluation_shader----"},

			s_shader{GL_GEOMETRY_SHADER, "\/\/----start_gl_geometry_shader----", "\/\/----end_gl_geometry_shader----"},

			s_shader{GL_FRAGMENT_SHADER, "\/\/----start_gl_fragment_shader----", "\/\/----end_gl_fragment_shader----"},
		};

		void compile();
	};
	typedef std::shared_ptr<c_shader> shader_t;
}