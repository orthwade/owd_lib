#include "c_sound_device.h"

namespace owd_lib
{
	c_sound_device* c_sound_device::m_singleton = nullptr;

	c_sound_device::c_sound_device()
	{
		m_logger << "openal_device constructor START\n";
	
		set_name(L"sound_device");
		m_logger.set_name(L"sound_device_logger");

		AL_CALL(m_openal_device = alcOpenDevice(0));

		AL_CALL(m_openal_context = alcCreateContext(m_openal_device, 0));

		AL_CALL(alcMakeContextCurrent(m_openal_context));
		
		m_logger << "openal_device constructor OK\n";
	}

	c_sound_device::~c_sound_device()
	{
		delete m_singleton;
	}

	c_sound_device* c_sound_device::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_sound_device();
		}
		return m_singleton;
	}

	ALCdevice* c_sound_device::get_openal_device()
	{
		return m_openal_device;
	}

	void c_sound_device::terminate()
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
}