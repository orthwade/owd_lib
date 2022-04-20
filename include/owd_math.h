#pragma once
#include <owd_misc.h>

namespace owd
{
	float cos_d(float angle_degrees);
	float sin_d(float angle_degrees);

	typedef std::array<float, 3> xyz_t; // array of space coordinates in Cartesian coordinate system

    /// <summary>
    /// array of orientaion coordinates in Cartesian coordinate system, 
    /// elements 0-2 are vector pointing where the object is "looking at"
    /// elements 3-5 are vector pointing whre the top of the object is pointing
    /// </summary>
    typedef std::array<float, 6> ori_t;

	struct s_2d_coordinates_cartesian
	{
		s_2d_coordinates_cartesian();
		s_2d_coordinates_cartesian(float x, float y);

		s_2d_coordinates_cartesian  operator+ (const s_2d_coordinates_cartesian& other);
		s_2d_coordinates_cartesian& operator+=(const s_2d_coordinates_cartesian& other);
		s_2d_coordinates_cartesian  operator- (const s_2d_coordinates_cartesian& other);
		s_2d_coordinates_cartesian& operator-=(const s_2d_coordinates_cartesian& other);
		s_2d_coordinates_cartesian  operator* (float multilpier);
		s_2d_coordinates_cartesian& operator*=(float multilpier);
		s_2d_coordinates_cartesian  operator/ (float divisor);
		s_2d_coordinates_cartesian& operator/=(float divisor);

		float x{};
		float y{};
	};

	typedef s_2d_coordinates_cartesian xy_t;

	class c_mat4
	{
	public:
		c_mat4();
		~c_mat4();
		void* operator()();
		void set_aspect_ratio(float aspect_ratio);
	private:
		void* m_data;
	};
	/// <summary>
	/// Object of a 3D-space vector with elements x, y, z.
	/// </summary>
	class c_3d_vector
	{
	public:
		c_3d_vector();
		c_3d_vector(float x, float y, float z);
		~c_3d_vector();

		c_3d_vector& operator=(const c_3d_vector& other);
		c_3d_vector(const c_3d_vector& other);

		void set(float x, float y, float z); // set vector elements
		xyz_t get(); // get vector elements
		float mangitude(); // get magnitude of the vector
		xyz_t norm(); // get normalized vector elements

		float x;
		float y;
		float z;

		/// <summary>
		/// Rotate vector around arbitrary axis u = (u_x, u_y, u_z).
		/// </summary>
		/// <param name="vec">Vector to rotate</param>
		/// <param name="angle">Angle in degrees to rotate vector</param>
		/// <param name="u_x">X component of a unit vector describing rotation axis</param>
		/// <param name="u_y">Y component of a unit vector describing rotation axis</param>
		/// <param name="u_z">Z component of a unit vector describing rotation axis</param>
		static void rotate_vector(c_3d_vector& vec, float angle, float u_x, float u_y, float u_z);

		c_3d_vector cross(const c_3d_vector& other);

	private:
	};

	/// <summary>
	/// Object contataining data and methods to handle orientation of the entity.
	/// Vector AT describes the direction where the entity is "looking" at.
	/// Vector UP describes the direction where the up of the entity is pointed at.
	/// Vectors AT and UP are perpendicular.
	/// Default value of AT: {0, 0, -1}.
	/// Default value of UP: {0, 1, 0}.
	/// </summary>
	class c_orientation
	{
	public:
		c_orientation();
		~c_orientation();
		
		/// <summary>
		/// Rotate orientation around OX', OY' or OZ' axes.
		/// OX', OY', OZ' do not necessarily match original axes OX, OY, OZ.
		/// OX' in general is the axis perpendicular both to AT and UP vectors(codirectional 
		/// with cross product of UP and AT vectors).
		/// OY' in general is the axis codirectional with UP vector.
		/// OZ' in general is the axis codirectional with AT vector.
		/// </summary>
		/// <param name="v">Angle in degrees to rotate orientation around OX' axis(vertical rotation).</param>
		/// <param name="h">Angle in degrees to rotate orientation around OY' axis(horizontal rotation)</param>
		/// <param name="r">Angle in degrees to rotate orientation around OZ' axis(roll)</param>
		void rotate(float v, float h, float r);

		/// <summary>
		/// Rotate vectors AT and UP around original axes OX, OY, OZ.
		/// </summary>
		/// <param name="v">Angle in degrees to rotate vectors AT and UP around OX axis</param>
		/// <param name="h">Angle in degrees to rotate vectors AT and UP around OY axis</param>
		/// <param name="r">Angle in degrees to rotate vectors AT and UP around OZ axis</param>
		void rotate_(float v, float h, float r);

		void set_default();

		/// <summary>
		/// Get array of elements of vector AT
		/// </summary>
		/// <returns></returns>
		xyz_t get_vec_at();
		/// <summary>
		/// Get array of elements of vector UP
		/// </summary>
		/// <returns></returns>
		xyz_t get_vec_up();

		ori_t ori{ 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		void update_from_public_array();

	private:
		c_3d_vector m_at{ 0.0f, 0.0f, -1.0f };
		c_3d_vector m_up{ 0.0f, 1.0f, 0.0f };

		//c_3d_vector m_at_buffer{ 0.0f, 0.0f, -1.0f };
		//c_3d_vector m_up_buffer{ 0.0f, 1.0f, 0.0f };

		c_logger m_logger{ L"3D vector" };

		c_3d_vector m_u{};
		c_3d_vector m_at_buffer{};
		c_3d_vector m_up_buffer{};

		xyz_t m_u_n{};

		float m_u_x{};
		float m_u_y{};
		float m_u_z{};

		/// <summary>
		/// Rotate vector vec around arbitrary axis u = (u_x, u_y, u_z).
		/// </summary>
		/// <param name="angle">Angle in degrees to rotate vector</param>
		/// <param name="u_x">X component of a unit vector describing rotation axis</param>
		/// <param name="u_y">Y component of a unit vector describing rotation axis</param>
		/// <param name="u_z">Z component of a unit vector describing rotation axis</param>
		void m_rotate(float angle, float u_x, float u_y, float u_z)
		{
			c_3d_vector::rotate_vector(m_at, angle, u_x, u_y, u_z);
			c_3d_vector::rotate_vector(m_up, angle, u_x, u_y, u_z);
			ori = { m_at.x, m_at.y, m_at.z, m_up.x, m_up.y, m_up.z };
		}
	};

}