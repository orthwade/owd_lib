#pragma once
#include "al.h"
#include "alc.h"
#include "alext.h"
#include "efx.h"
#include "efx-creative.h"
#include "efx-presets.h"

#pragma comment(lib, "OpenAL32.lib")

#include <owd_debug.h>


namespace owd_lib
{
	class c_oal_debug
	{
	public:
		static c_oal_debug* get_instance();
		static void terminate();

		std::wstring_view error_view(ALenum error_code);

		bool al_log_call();

	protected:
		owd::c_logger al_logger{ L"al_logger" };
		std::wstring al_error_str{};

		static c_oal_debug* m_singleton;

		c_oal_debug();
		~c_oal_debug();

		c_oal_debug(const c_oal_debug&) = delete;
		c_oal_debug& operator=(const c_oal_debug&) = delete;
	};
}
#define AL_CALL(x)											\
{															\
	auto oal_debug = owd_lib::c_oal_debug::get_instance();	\
	x;														\
	ASSERT(oal_debug->al_log_call())						\
}