#include "c_texture_bank.h"

namespace owd_lib
{
	c_texture_bank* c_texture_bank::m_singleton = nullptr;

	c_texture_bank* c_texture_bank::get_instance()
	{
		if (m_singleton == nullptr)
		{
			m_singleton = new c_texture_bank();
		}

		return m_singleton;
	}
	void c_texture_bank::terminate()
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
	c_texture_bank::c_texture_bank()
	{
	}
	c_texture_bank::~c_texture_bank()
	{
	}
}
