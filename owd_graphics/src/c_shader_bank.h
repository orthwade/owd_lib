#pragma once
#include <owd_filesystem.h>

#include "c_shader.h"

namespace owd_lib
{
	class c_shader_bank : public owd::c_file_bank<c_shader>
	{
	public:
		static c_shader_bank* get_instance();
		static void terminate();

	private:
		static c_shader_bank* m_singleton;

		c_shader_bank();
		~c_shader_bank();
		
		c_shader_bank(const c_shader_bank&) = delete;
		c_shader_bank& operator=(const c_shader_bank&) = delete;
	};
}