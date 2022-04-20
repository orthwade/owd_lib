#pragma once
#include "c_glsl_uniform.h"

#include <owd_math.h>

namespace owd_lib
{
	class c_mat4_uniform : public c_glsl_uniform
	{
	public:
		c_mat4_uniform();
		~c_mat4_uniform();

		c_mat4_uniform(const c_mat4_uniform& other);
		c_mat4_uniform& operator=(const c_mat4_uniform& other);

		//void set_name(std::wstring_view name);

		//std::wstring_view name()
		//{
		//	return m_name;
		//}

		void init(uint32_t shader_program_id) override;
		void init(uint32_t shader_program_id, owd::c_mat4& glm_mat4);

		void set(owd::c_mat4& glm_mat4);

		//int32_t get_location()
		//{
		//	if (m_uniform_location == -1)
		//	{
		//		GL_CALL(m_uniform_location = glGetUniformLocation(m_shader_program_id, "u_colour"));
		//	}
		//	return m_uniform_location;
		//}

	private:
		std::wstring m_name{ L"c_mat4_uniform_object" };
		//std::wstring m_uniform_name{ "u_Color" };
		owd::c_logger m_logger{ L"c_mat4_uniform", owd::logger_mode_both };
		//std::recursive_mutex m_mtx{};

		//uint32_t m_shader_program_id{};

		owd::c_mat4 m_mat4{};

		//int32_t m_uniform_location = -1;
	};
}
