#include <stdint.h>
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <thread>
#include <mutex>
#include <vector>
#include <list>

#include <owd_math.h>
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
			owd::c_graphic_unit unit_0{ 0.0f, 0.0f, 100.0f, 100.0f, 0.8f, 0.8f, 0.8f, 1.0f, 0 };

			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			// 4. 2. Play sound source
			//sound_1.enable({ L"sample1" });

			// 4. 3. Load texture from png file.
			owd::load_texture(L"rsc/textures/a_orange.png", L"A orange");
			owd::load_texture(L"rsc/textures/digits/0.png", L"0");
			owd::load_texture(L"rsc/textures/digits/1.png", L"1");

			// 4. 4. Create 256 textured squares.

			int32_t count_ = 256;

			std::vector<std::shared_ptr<owd::c_graphic_unit>> vec_unit{};
			
			for (int32_t i = 0; i != count_; ++i)
			{
				float x = owd::rand(-0.9f, 0.9f);
				float y = owd::rand(-0.9f, 0.9f);
				int t = owd::rand(0.0f, 2.9f);

				switch (t)
				{
				case 0:
					vec_unit.push_back(std::make_shared<owd::c_graphic_unit>(x, y, 0.1f, 0.1f, L"A orange", 2));
					break;
				case 1:
					vec_unit.push_back(std::make_shared<owd::c_graphic_unit>(x, y, 0.1f, 0.2f, L"0", 2));
					break;
				case 2:
					vec_unit.push_back(std::make_shared<owd::c_graphic_unit>(x, y, 0.1f, 0.2f, L"1", 2));
					break;
				default:
					vec_unit.push_back(std::make_shared<owd::c_graphic_unit>(x, y, 0.1f, 0.2f, L"0", 2));
					break;
				}
				
			}

			std::vector<owd::xy_t> vec_delta{};

			float delta_x = 1.0f / owd::fps();
			float delta_y = delta_x;

			for (int32_t i = 0; i != count_; ++i)
			{
				vec_delta.push_back({ delta_x, delta_y });
				auto rand_1 = owd::rand(-1.0f, 1.0f);
				auto rand_2 = owd::rand(-1.0f, 1.0f);
				rand_1 /= std::abs(rand_1);
				rand_2 /= std::abs(rand_1);
				vec_delta.back().x *= rand_1;
				vec_delta.back().y *= rand_2;
			}

			std::mutex mtx{};
			while (!owd::window_should_close())
			//while (true)
			{
				// 4. 5. Loop and thread will be ended and when GLFW window is closed.

				// 4. 6. wait_frame and set_entities to sync screen update().
				owd::wait_frame();
				owd::set_entities_wait();
				//std::lock_guard lock(mtx);
				if (!running)
				{
					break;
				}
				for (int32_t i = 0; i != count_; ++i)
				{
					auto& unit = vec_unit[i];
					auto& _x = vec_delta[i].x;
					auto& _y = vec_delta[i].y;

					if (unit->y() < -1.0f)
					{
						_y *= -1;
					}
					else if (unit->y() > 1.0f)
					{
						_y *= -1;
					}
					if (unit->x() < -1.0f)
					{
						_x *= -1;
					}
					else if (unit->x() > 1.0f)
					{
						_x *= -1;
					}

					vec_unit[i]->move(vec_delta[i].x, vec_delta[i].y);
				}
				
				owd::set_entities_ready();
				//std::wcout << "X: " << owd::mouse_x() << ";    Y: " << owd::mouse_y() << '\n';
				//owd::update_window();
				//std::this_thread::sleep_for(std::chrono::milliseconds(1));
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