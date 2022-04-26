#pragma once
#include <stdint.h>
#include "../../owd_graphics/src/c_graphic_engine.h"

namespace owd_lib
{
	void key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
	void mouse_button_callback(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);

	enum class enm_key_state
	{
		press,
		release,
		idle
	};
	constexpr enm_key_state key_press = enm_key_state::press;
	constexpr enm_key_state key_release = enm_key_state::release;
	constexpr enm_key_state key_idle = enm_key_state::idle;

	struct s_key
	{
		int32_t key{};
		enm_key_state state = key_idle;
	};

	class c_input_manager
	{
	public:
		inline std::vector<s_key>& keys() { return m_keys; }
		s_key& get_key(int32_t key_code);

		static c_input_manager* get_instance();
		static void terminate();

	protected:
		std::mutex m_mutex{};
		std::vector<s_key> m_keys{};
		static c_input_manager* m_singleton;

		c_input_manager();
		~c_input_manager();

		c_input_manager(const c_input_manager&) = delete;
		c_input_manager& operator=(const c_input_manager&) = delete;
	};
}