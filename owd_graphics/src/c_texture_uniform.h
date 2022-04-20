#pragma once
#include "c_glsl_uniform.h"

namespace owd_lib
{
	class c_texture_uniform : public c_glsl_uniform
	{
	public:
		c_texture_uniform();
		~c_texture_uniform();

		c_texture_uniform(const c_texture_uniform& other);
		c_texture_uniform& operator=(const c_texture_uniform& other);

		//void set_name(std::wstring_view name);

		//std::wstring_view name()
		//{
		//	return m_name;
		//}

		void init(uint32_t shader_program_id) override;
		void init(uint32_t shader_program_id, int32_t sampler_id);
		void init(uint32_t shader_program_id, std::vector<int32_t> vec_sampler_id);

		void set(int32_t sampler_id);

		//int32_t get_location()
		//{
		//	if (m_uniform_location == -1)
		//	{
		//		GL_CALL(m_uniform_location = glGetUniformLocation(m_shader_program_id, "u_colour"));
		//	}
		//	return m_uniform_location;
		//}

	private:
		std::wstring m_name{ L"c_texture_uniform_object" };
		//std::wstring m_uniform_name{ "u_Color" };
		owd::c_logger m_logger{ L"c_texture_uniform", owd::logger_mode_both };
		//std::recursive_mutex m_mtx{};

		//uint32_t m_shader_program_id{};

		int32_t m_sampler_id{};
		std::vector<int32_t> m_vec_sampler_id{};

		//int32_t m_uniform_location = -1;
	};
}
