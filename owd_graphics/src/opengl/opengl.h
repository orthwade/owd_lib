#pragma once
#include <vector>

#include <owd_debug.h>

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")

namespace owd_lib
{
	typedef GLuint gl_index_t;
	typedef std::vector<gl_index_t> gl_indices_t;

	GLint gl_int32_param(GLenum param);

	class c_ogl_debug
	{
	public:
		static c_ogl_debug* get_instance();
		static void terminate();

		std::wstring_view error_view(GLenum error_code);

		void gl_clear_error();

		bool gl_log_call();

	protected:
		owd::c_logger gl_logger{ L"gl_logger" };
		std::wstring gl_error_str{};

		static c_ogl_debug* m_singleton;

		c_ogl_debug();
		~c_ogl_debug();

		c_ogl_debug(const c_ogl_debug&) = delete;
		c_ogl_debug& operator=(const c_ogl_debug&) = delete;
	};
}

#define GL_CALL(x)											\
{															\
	auto ogl_debug = owd_lib::c_ogl_debug::get_instance();	\
	ogl_debug->gl_clear_error();							\
	x;														\
	ASSERT(ogl_debug->gl_log_call())						\
}