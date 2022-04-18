#pragma once
#include "c_openal_object.h"

namespace owd_lib
{
	class c_sound_device : public c_openal_object
	{
	public:
		ALCdevice* get_openal_device();
		static c_sound_device*	get_instance();
		void terminate();

	protected:
		ALCdevice*	m_openal_device = nullptr;
		ALCcontext* m_openal_context = nullptr;

		std::wstring	m_dvc_list_name{};
		std::wstring	m_default_dvc_name{};
		std::wstring	m_dvc_name{};


		static c_sound_device* m_singleton;
		c_sound_device();

		~c_sound_device();

	};
}


