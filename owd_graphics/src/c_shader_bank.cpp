#include "c_shader_bank.h"

namespace owd_lib
{
	c_shader_bank* c_shader_bank::m_singleton = nullptr;
	
	c_shader_bank* c_shader_bank::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_shader_bank();
		}

		return m_singleton;
	}
	void c_shader_bank::terminate()
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
    c_shader_bank::c_shader_bank()
    {
    }
    c_shader_bank::~c_shader_bank()
    {
    }
}
