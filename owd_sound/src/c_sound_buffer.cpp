#include "c_sound_buffer.h"

namespace owd_lib
{
	c_sound_buffer::c_sound_buffer()
	{
		m_gen_buffer();
	}
	c_sound_buffer::~c_sound_buffer()
	{
	
		m_logger << "----sound buffer destructor START----\n";
		if (m_openal_buffer_ptr != 0)
		{
			release();
		}
		m_logger << "----sound buffer destructor OK----\n";
	}

	void c_sound_buffer::set_data(void* data, ALsizei bytes_count, ALsizei freq, ALenum format)
	{
		//m_mtx.lock();
		{
			AL_CALL(alBufferData(m_openal_buffer_ptr, format, data, bytes_count, freq));
		}
		//m_mtx.unlock();
	}
	ALuint& c_sound_buffer::openal_buffer()
	{
		return m_openal_buffer_ptr;
	}
	void c_sound_buffer::release()
	{
		AL_CALL(alDeleteBuffers(1, &m_openal_buffer_ptr));
	}
	void c_sound_buffer::m_gen_buffer()
	{
		m_logger << "----Generating sound buffer START----\n";

		AL_CALL(alGenBuffers(1, &m_openal_buffer_ptr));
	}
}