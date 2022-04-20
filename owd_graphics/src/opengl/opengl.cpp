#include "opengl.h"

namespace owd_lib
{
	GLint gl_int32_param(GLenum param)
	{
		GLint result{};
		glGetIntegerv(param, &result);
		return result;
	}
	c_ogl_debug* c_ogl_debug::m_singleton = nullptr;

	c_ogl_debug* owd_lib::c_ogl_debug::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_ogl_debug();
		}

		return m_singleton;
	}

	void c_ogl_debug::terminate()
	{
		if (m_singleton == nullptr)
		{

		}
		else
		{
			delete m_singleton;
			m_singleton = nullptr;
		}
	}
	std::wstring_view c_ogl_debug::error_view(GLenum error_code)
	{
		switch (error_code)
		{
		case	GL_INVALID_ENUM:
			gl_error_str =
				L"[GL_INVALID_ENUM] An unacceptable value is specified for an enumerated argument.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_INVALID_VALUE:
			gl_error_str =
				L"[GL_INVALID_VALUE] A numeric argument is out of range.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_INVALID_OPERATION:
			gl_error_str =
				L"[GL_INVALID_OPERATION] The specified operation is not allowed in the current state.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_STACK_OVERFLOW:
			gl_error_str =
				L"[GL_STACK_OVERFLOW] This function would cause a stack overflow.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_STACK_UNDERFLOW:
			gl_error_str =
				L"[GL_STACK_UNDERFLOW] This function would cause a stack underflow.\n"
				"The offending function is ignored, having no side effect other than to set the error flag.\n";
			break;

		case	GL_OUT_OF_MEMORY:
			gl_error_str =
				L"[GL_OUT_OF_MEMORY] There is not enough memory left to execute the function.\n"
				"The state of OpenGL is undefined, except for the state of the error flags, after this error is recorded.\n";
			break;

		default:
			gl_error_str = L"uknown error";
			break;

		}
		return gl_error_str;
	}
	void c_ogl_debug::gl_clear_error()
	{
		GLenum error{};
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			if (error != GL_NO_ERROR)
			{
				gl_logger << L"----OpenGL CLEAR ERRORS: ERROR_CODE:\n" << error_view(error) << '\n';
			}
			else
			{
				gl_logger << L"----OpenGL CLEAR ERRORS: NO ERROR\n";
			}
		}
	}
	bool c_ogl_debug::gl_log_call()
	{
		while (GLenum error = glGetError())
		{
			if (error != GL_NO_ERROR)
			{
				gl_logger << L"----OpenGL call ERROR:\n" << error_view(error) << '\n';
				return false;
			}
		}
		gl_logger << L"----OpenGL call SUCCESS\n";
		return true;
	}
	c_ogl_debug::c_ogl_debug()
	{
	}
	c_ogl_debug::~c_ogl_debug()
	{
	}
}