#include "c_sound_source_bank.h"

namespace owd_lib
{
	c_sound_source_bank* c_sound_source_bank::m_singleton = nullptr;
	
	c_sound_source_bank* owd_lib::c_sound_source_bank::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_sound_source_bank();
		}

		return m_singleton;
	}
	void c_sound_source_bank::terminate()
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
    c_sound_source_bank::c_sound_source_bank()
    {
    }
    c_sound_source_bank::~c_sound_source_bank()
    {
    }
}
