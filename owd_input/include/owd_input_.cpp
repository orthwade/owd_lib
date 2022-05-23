#include "owd_input_.h"
#include "../src/c_input_manager.h"

namespace owd
{
	static uint8_t convert_to_int(owd_lib::enm_key_state& state)
	{
		if (state == owd_lib::key_idle)
		{
			return owd::key_idle;
		}
		else if (state == owd_lib::key_press)
		{
			return owd::key_press;
		}
		else if (state == owd_lib::key_release)
		{
			return owd::key_release;
		}
	}

	double mouse_x()
	{
		return owd_lib::c_input_manager::get_instance()->mouse_x();
	}

	double mouse_y()
	{
		return owd_lib::c_input_manager::get_instance()->mouse_y();
	}

	owd::s_key owd::get_key(int32_t key_code)
	{
		auto key_ = owd_lib::c_input_manager::get_instance()->get_key(key_code);
		auto key_code_ = key_.key;
		auto key_state_ = convert_to_int(key_.state);
		return { key_code_, key_state_ };
	}
	
	void owd::set_key_idle(int32_t key_code)
	{
		owd_lib::c_input_manager::get_instance()->get_key(key_code).state = owd_lib::key_idle;
	}
}