#pragma once
#include <string_view>
#include <vector>

namespace owd
{
	void run();
	void terminate();

	void load_texture(std::wstring_view filepath, std::wstring_view name);
	void remove_texture(std::wstring_view name);
	void clear_textures();

	enum class enm_graphic_unit
	{
		coloured,
		textured
	};

	constexpr enm_graphic_unit coloured_unit = enm_graphic_unit::coloured;
	constexpr enm_graphic_unit textured_unit = enm_graphic_unit::textured;

	void set_entities_wait();
	void set_entities_ready();

	void update_window();
	bool window_should_close();

	void wait_frame();
	float fps();
	/// <summary>
	/// Graphic unit. Coloured rectangle, textured rectangle, coloured 2D-figure.
	/// </summary>
	class c_graphic_unit
	{
	public:
		/// <summary>
		/// Creates coloured 2D-figure.
		/// </summary>
		/// <param name="positions">Vector of XY coordinates of unique vertices. 
		/// For example, if c_graphic_unit is square [-1, -1, 1, -1, 1, 1, -1, 1]</param>
		/// <param name="indices">Vector of indices of triangle vertices. 
		/// For example, if c_graphic_unit is square [0, 1, 2, 2, 3, 0]</param>
		/// <param name="r">Red colour compenent</param>
		/// <param name="g">Green colour compenent</param>
		/// <param name="b">Blue colour compenent</param>
		/// <param name="a">Alpha channel</param>
		/// <param name="l"></param>
		c_graphic_unit(const std::vector<float>& positions, const std::vector<uint32_t>& indices,
			float r, float g, float b, float a, uint16_t l);

		/// <summary>
		/// Create coloured rectangle.
		/// </summary>
		/// <param name="x">Centre X coordinate</param>
		/// <param name="y">Centre Y coordinate</param>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		/// <param name="r">Red colour compenent</param>
		/// <param name="g">Green colour compenent</param>
		/// <param name="b">Blue colour compenent</param>
		/// <param name="a">Alpha channel</param>
		/// <param name="l">Level. Defines position above or below other units. 
		/// Higher level is above, lower - below.</param>
		c_graphic_unit(float x, float y, float w, float h,
			float r, float g, float b, float a, uint16_t l);

		/// <summary>
		/// Create coloured circle.
		/// </summary>
		/// <param name="x">Centre X coordinate</param>
		/// <param name="y">Centre Y coordinate</param>
		/// <param name="radius">Radius</param>
		/// <param name="r">Red colour compenent</param>
		/// <param name="g">Green colour compenent</param>
		/// <param name="b">Blue colour compenent</param>
		/// <param name="a">Alpha channel</param>
		/// <param name="l">Level. Defines position above or below other units. 
		/// Higher level is above, lower - below.</param>
		c_graphic_unit(float x, float y, float radius,
			float r, float g, float b, float a, uint16_t l);

		/// <summary>
		/// Create textured rectangle.
		/// </summary>
		/// <param name="x">Centre X coordinate</param>
		/// <param name="y">Centre Y coordinate</param>
		/// <param name="w">Width</param>
		/// <param name="h">Height</param>
		/// <param name="t">Texture name. Texture should be loaded with load_texture function beforehand.</param>
		/// <param name="l">Level. Defines position above or below other units. 
		/// Higher level is above, lower - below.</param>
		c_graphic_unit(float x, float y, float w, float h,
			std::wstring_view t, uint16_t l);

		~c_graphic_unit();

		enm_graphic_unit type();

		float x();
		float y();

		void resize(float multiplier);

		void set_position(float x, float y);

		void move(float d_x, float d_y);

	private:
		enm_graphic_unit m_type;
		void* m_data;
	};
}