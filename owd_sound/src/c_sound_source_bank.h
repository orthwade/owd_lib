#pragma once
#include <owd_misc.h>

#include "c_sound_source.h"

namespace owd_lib
{
	class c_sound_source_bank : public owd::c_object_bank<c_sound_source_lib>
	{
	public:
		static c_sound_source_bank* get_instance();
		static void terminate();

	protected:
		static c_sound_source_bank* m_singleton;

		c_sound_source_bank();
		~c_sound_source_bank();
		
		c_sound_source_bank(const c_sound_source_bank&) = delete;
		c_sound_source_bank& operator=(const c_sound_source_bank&) = delete;
		
	};
}