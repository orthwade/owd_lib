#pragma once
#include "c_glsl_uniform.h"

namespace owd_lib
{
	class c_colour_uniform : public c_glsl_uniform
	{
	public:
		c_colour_uniform();
		~c_colour_uniform();

		c_colour_uniform(const c_colour_uniform& other);
		c_colour_uniform& operator=(const c_colour_uniform& other);

		//void set_name(std::wstring_view name);

		//std::wstring_view name()
		//{
		//	return m_name;
		//}
		
		void init(uint32_t shader_program_id) override;
		void init(uint32_t shader_program_id, float red, float green, float blue, float alpha);

		void set(c_colour_uniform& other);
		void set(float red, float green, float blue, float alpha);
		void set(float red, float green, float blue, float alpha, uint32_t shader_program_id);

		//int32_t get_location()
		//{
		//	if (m_uniform_location == -1)
		//	{
		//		GL_CALL(m_uniform_location = glGetUniformLocation(m_shader_program_id, "u_colour"));
		//	}
		//	return m_uniform_location;
		//}

	private:
		std::wstring m_name{ L"c_colour_uniform_object" };
		//std::wstring m_uniform_name{ "u_Color" };
		owd::c_logger m_logger{ L"c_colour_uniform", owd::logger_mode_both };
		//std::recursive_mutex m_mtx{};

		//uint32_t m_shader_program_id{};

		float m_r{};
		float m_g{};
		float m_b{};
		float m_a{};

		//int32_t m_uniform_location = -1;
	};
}
