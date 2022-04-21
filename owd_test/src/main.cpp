#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#include <stdint.h>
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <thread>

#include <owd_misc.h>
#include <owd_strings.h>
#include <owd_time.h>
#include <owd_debug.h>
#include <owd_sound.h>
#include <owd_filesystem.h>
#include <owd_graphics.h>

#pragma comment(lib, "owd_misc.lib")

int32_t main()
{
	static auto setmode_result = _setmode(_fileno(stdout), _O_WTEXT);
	owd::c_logger::set_global_mode_override(1);
	owd::c_logger::enable_global_mode_override();
	//const char* c_str_1		= "UTF-8 char string";
	//const wchar_t* wc_str_1 = L"UNICODE char string ¿¡¿œ»¡¡";
	//std::wstring wstring_	= L"UNICODE string ‘€¬ ‘€";
	//auto convert_to_unicode = owd::unicode(c_str_1);
	//auto convert_to_utf_8	= owd::utf_8(wc_str_1);

	//std::wcout << wstring_ << '\n';
	//std::wcout << wc_str_1 << '\n';
	//std::wcout << c_str_1 << '\n';

	//std::wcout << convert_to_unicode << '\n';
	//std::wcout << convert_to_utf_8.c_str() << '\n';

	//std::wcout << owd::time_date().c_str() << '\n';

	//auto timer = owd::c_async_timer();
	//auto& contents_str = owd::directory_contents(L"C:/Program Files");
	//auto& files_str = owd::files_in_directory(L"C:/Program Files");
	//auto& folders_str = owd::folders_in_directory(L"C:/Program Files");

	//for (int i = 0; i < 10; ++i)
	//{
	//	timer.wait();
	//	std::wcout << "Timer: " << i << '\n';
	//	timer.start(10000);
	//}
	//
	owd::c_logger logger{ L"Test_logger" };
	//logger.disable_global_mode_override();
	//logger << L"Test message ‡ÙÍ‡˚‚Ô‡‚˚Ô\n";

	//auto basic_object = owd::c_basic_object();
	//logger << basic_object.name() << '\n';

	//for (auto& unit : files_str)
	//{
	//	logger << unit << '\n';
	//}
	//for (auto& unit : folders_str)
	//{
	//	logger << unit << '\n';
	//}
	//for (auto& unit : contents_str)
	//{
	//	logger << unit << '\n';
	//}
	auto file_1 = owd::c_file();
	file_1.load(L"C:/Program Files/_1.txt");
	//auto text_1 = owd::c_textfile();
	//text_1.load(L"C:/Program Files/_1.txt");
	auto text_2 = owd::c_textfile();
	text_2.load(L"C:/Program Files/_2.txt");
	//logger << text_1.str() << '\n';
	logger << text_2.view() << '\n';
	//auto test_extern = owd::c_test_extern();
	//logger << test_extern << '\n';
	//std::wcout << wstring_ << '\n';
//	auto time = owd::
	auto listener = owd::c_listener::get_instance();
	listener->set_default_orientation();
	listener->set_position(0.0f, 0.0f, 0.0f);
	listener->set_gain(0.99);
	auto sound_1 = owd::c_sound_source(L"");

	//sound_1.load_sound(L"C:/Users/boba/Downloads/sample1.ogg", L"sample1");
	sound_1.load_sound(L"C:/Users/boba/Downloads/Rear_left.ogg", L"sample1");
	sound_1.set_position(-1.0f, 0.0f, -9.0f);
	sound_1.set_gain(0.99f);
	
	
	auto lambda_ = [&]()
	{ owd::c_graphic_unit unit{ 0.0f, 0.1f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 1 }; 
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	sound_1.enable({ L"sample1" });
	owd::load_texture(L"rsc/textures/a_orange.png", L"A orange");
	owd::c_graphic_unit unit_t_1{ 0.5f, 0.0f, 0.2f, 0.2f, L"A orange", 2 };
	while (true) {}};
	auto thread_ = std::thread(lambda_);

	owd::run();



	return 0;
}