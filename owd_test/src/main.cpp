#include <stdint.h>
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <thread>
#include <mutex>

#include <owd_misc.h>
#include <owd_strings.h>
#include <owd_time.h>
#include <owd_debug.h>
#include <owd_sound.h>
#include <owd_filesystem.h>
#include <owd_graphics.h>
#include <owd_input.h>

int32_t main()
{
	static auto setmode_result = _setmode(_fileno(stdout), _O_WTEXT);

	//----EXAMPLES START----//
	{
		// 1. Set global logger mode to "none". Logger input is ignored.
		owd::c_logger::set_global_mode_override(0);

		// 2. Enable override logger mode. 
		// Specific logger object mode will ignore their private modes and will behave according to the global mode
		owd::c_logger::enable_global_mode_override();

		// 3. Sound examples
		
		// 3. 1. Set listener
		auto listener = owd::c_listener::get_instance();
		listener->set_default_orientation();
		listener->set_position(0.0f, 0.0f, 0.0f);
		listener->set_gain(0.99);

		// 3. 2. Set sound source
		auto sound_1 = owd::c_sound_source(L"");

		sound_1.load_sound(L"rsc/sounds/misc/Rear_left.ogg", L"sample1");
		sound_1.set_position(-1.0f, 0.0f, -9.0f);
		sound_1.set_gain(0.99f);

		// 4. Simple game pipeline
		std::atomic_bool running = true;

		auto game_ = [&]()
		{ 
			// 4. 1. Create white square
			owd::c_graphic_unit unit{ 0.0f, 0.1f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 1 };

			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			// 4. 2. Play sound source
			sound_1.enable({ L"sample1" });

			// 4. 3. Load texture from png file.
			owd::load_texture(L"rsc/textures/a_orange.png", L"A orange");

			// 4. 4. Create textured square.
			owd::c_graphic_unit unit_t_1{ 0.5f, 0.0f, 0.2f, 0.2f, L"A orange", 2 };

			float delta_x = 0.001f;
			float delta_y = 0.001f;
			std::mutex mtx{};
			while (true)
			{
				// 4. 5. Loop and thread will be ended and when GLFW window is closed.
				std::lock_guard lock(mtx);
				if (!running)
				{
					break;
				}
				auto f_t = unit_t_1.y();

				if (unit_t_1.y() < -1.0f)
				{
					delta_y *= -1;
				}
				else if (unit_t_1.y() > 1.0f)
				{
					delta_y *= -1;
				}
				if (unit_t_1.x() < -1.0f)
				{
					delta_x *= -1;
				}
				else if (unit_t_1.x() > 1.0f)
				{
					delta_x *= -1;
				}
				owd::sleep_for_ms(1); unit_t_1.move(delta_x, delta_y);
			}
		};
		// 5. Set thread.
		auto thread_ = std::thread(game_);

		// 6. Start updating the window. owd::run will work until the window is closed.
		owd::run();
		
		// 7. Close the window and deinitialize graphics.
		owd::terminate();
		running = false;
		thread_.join();
	}
	//----EXAMPLES END----//

	
	return 0;
}