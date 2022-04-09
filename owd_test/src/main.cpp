#include <stdint.h>
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>

//#pragma comment(lib, "owd_strings.lib")

#include <owd_strings.h>
#include <owd_time.h>
#include <owd_time.h>
#include <owd_debug.h>

int32_t main()
{
	static auto setmode_result = _setmode(_fileno(stdout), _O_WTEXT);
	const char* c_str_1		= "UTF-8 char string";
	const wchar_t* wc_str_1 = L"UNICODE char string ¿¡¿œ»¡¡";
	std::wstring wstring_	= L"UNICODE string ‘€¬ ‘€";
	auto convert_to_unicode = owd::unicode(c_str_1);
	auto convert_to_utf_8	= owd::utf_8(wc_str_1);

	std::wcout << wstring_ << '\n';
	std::wcout << wc_str_1 << '\n';
	std::wcout << c_str_1 << '\n';

	std::wcout << convert_to_unicode << '\n';
	std::wcout << convert_to_utf_8.c_str() << '\n';

	std::wcout << owd::time_date().c_str() << '\n';

	auto timer = owd::c_async_timer();

	for (int i = 0; i < 10; ++i)
	{
		timer.wait();
		std::wcout << "Timer: " << i << '\n';
		//timer.start(1000000);
	}
	owd::c_logger logger{ L"Test_logger" };
	logger.disable_global_mode_override();
	logger << "Test message\n";
	//std::wcout << wstring_ << '\n';
//	auto time = owd::
	return 0;
}