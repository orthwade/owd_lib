#include "owd_math_.h"

namespace owd
{
	c_3d_vector::c_3d_vector()
		: c_3d_vector(0.0f, 0.0f, 0.0f)
	{
	}
	c_3d_vector::c_3d_vector(float _x, float _y, float _z)
		:
		x(_x),
		y(_y),
		z(_z)
	{
	}
	c_3d_vector::~c_3d_vector()
	{
	}
	c_3d_vector& c_3d_vector::operator=(const c_3d_vector& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}
	c_3d_vector::c_3d_vector(const c_3d_vector& other)
	{
		*this = other;
	}
	void c_3d_vector::set(float in_x, float in_y, float in_z)
	{
		x = in_x;
		y = in_y;
		z = in_z;
	}
	xyz_t c_3d_vector::get()
	{
		xyz_t result{};

		result[0] = x;
		result[1] = y;
		result[2] = z;

		return result;
	}
	float c_3d_vector::mangitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	xyz_t c_3d_vector::norm()
	{
		xyz_t result{};

		float magnitude = sqrtf(x * x + y * y + z * z);
		result[0] = x / magnitude;
		result[1] = y / magnitude;
		result[2] = z / magnitude;

		return result;
	}
	void c_3d_vector::rotate_vector(c_3d_vector& vec, float angle, float u_x, float u_y, float u_z)
	{
		float x_ = vec.x;
		float y_ = vec.y;
		float z_ = vec.z;

		angle = angle * pi_ / 180.0f;

		vec.x =
			u_x * (u_x * x_ + u_y * y_ + u_z * z_)
			- ((-1 + u_x * u_x) * x_ + u_x * (u_y * y_ + u_z * z_)) * cosf(angle)
			+ (-(u_z * y_) + u_y * z_) * sinf(angle);

		vec.y =
			u_y * (u_x * x_ + u_y * y_ + u_z * z_)
			- (u_x * u_y * x_ + (-1 + u_y * u_y) * y_ + u_y * u_z * z_) * cosf(angle)
			+ (u_z * x_ - u_x * z_) * sinf(angle);

		vec.z =
			u_z * (u_x * x_ + u_y * y_ + u_z * z_)
			- (u_x * u_z * x_ + u_y * u_z * y_ + (-1 + u_z * u_z) * z_) * cosf(angle)
			+ (-(u_y * x_) + u_x * y_) * sinf(angle);
	}
	c_3d_vector c_3d_vector::cross(const c_3d_vector& other)
	{
		c_3d_vector a{};
		c_3d_vector b{};
		c_3d_vector c{};
		
		a = *this;
		b = other;

		c.x = a.y * b.z - a.z * b.y;
		c.y = a.z * b.x - a.x * b.z;
		c.z = a.x * b.y - a.y * b.x;

		return c;
	}

	c_orientation::c_orientation()
	{
		m_logger << "----orientation constructor START----\n";

		

		m_logger << "----orientation constructor OK----\n";
	}
	c_orientation::~c_orientation()
	{
		m_logger << "----orientation destructor START----\n";
		m_logger << "----orientation destructor OK----\n";
	}
	void c_orientation::rotate(float v, float h, float r)
	{
		//m_mtx.lock();
		{
			m_at_buffer = m_at;
			m_up_buffer = m_up;

			// OX' rotation:
			{
				m_u = m_up_buffer.cross(m_at_buffer);

				m_u_n = m_u.norm();

				m_u_x = m_u_n[0];
				m_u_y = m_u_n[1];
				m_u_z = m_u_n[2];

				m_rotate(v, m_u_z, m_u_y, m_u_z);
			}

			// OY' rotation:
			{
				m_u = m_up_buffer;

				m_u_n = m_u.norm();

				m_u_x = m_u_n[0];
				m_u_y = m_u_n[1];
				m_u_z = m_u_n[2];

				m_rotate(h, m_u_z, m_u_y, m_u_z);
			}

			// OZ' rotation:
			{
				m_u = m_at_buffer;

				m_u_n = m_u.norm();

				m_u_x = m_u_n[0];
				m_u_y = m_u_n[1];
				m_u_z = m_u_n[2];

				m_rotate(r, m_u_z, m_u_y, m_u_z);
			}
		}
		//m_mtx.unlock();
	}
	void c_orientation::rotate_(float v, float h, float r)
	{
		//m_mtx.lock();
		{
			// OX' rotation:
			{
				m_rotate(v, 1.0f, 0.0f, 0.0f);
			}

			// OY' rotation:
			{
				m_rotate(h, 0.0f, 1.0f, 0.0f);
			}

			// OZ' rotation:
			{
				m_rotate(r, 0.0f, 0.0f, 1.0f);
			}
		}
		//m_mtx.unlock();
		
	}
	void c_orientation::set_default()
	{
		//m_mtx.lock();
		{
			m_at.set(0.0, 0.0f, -1.0f);
			m_up.set(0.0, 1.0f, 0.0f);
			ori = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
		}
		//m_mtx.unlock();
	}
	xyz_t c_orientation::get_vec_at()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			result[0] = m_at.x;
			result[1] = m_at.y;
			result[2] = m_at.z;
		}
		//m_mtx.unlock();

		return result;
	}
	xyz_t c_orientation::get_vec_up()
	{
		xyz_t result{};

		//m_mtx.lock();
		{
			result[0] = m_up.x;
			result[1] = m_up.y;
			result[2] = m_up.z;
		}
		//m_mtx.unlock();

		return result;
	}
	void c_orientation::update_from_public_array()
	{
		m_at.set(ori[0], ori[1], ori[2]);
		m_up.set(ori[3], ori[4], ori[5]);
	}
	//void c_orientation::m_calculate_angle()
	//{
	//	//m_calculate_magnitude();
	//	m_calculate_normalized();
	//	//m_mtx.lock();
	//	{
	//		m_logger << "Calculating angle\n";
	//		// X rotation:
	//
	//		if (m_norm_y <= 0.0f && m_norm_z >= 0.0f) //alpha
	//		{
	//			m_angle_x = acosf(m_norm_z) * 180.0f / PI;
	//		}
	//		else if (m_norm_y <= 0.0f && m_norm_z <= 0.0f) // beta
	//		{
	//			m_angle_x = asinf(abs(m_norm_z)) * 180.0f / PI + 90.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_z <= 0.0f) // gamma
	//		{
	//			m_angle_x = asinf(m_norm_y) * 180.0f / PI + 180.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_z >= 0.0f) // phi
	//		{
	//			m_angle_x = 360.0f - acosf(m_norm_z) * 180.0f / PI;
	//		}
	//
	//		// Y rotation:
	//
	//		if (m_norm_z <= 0.0f && m_norm_x >= 0.0f) //alpha
	//		{
	//			m_angle_y = acosf(m_norm_x) * 180.0f / PI;
	//		}
	//		else if (m_norm_z <= 0.0f && m_norm_x <= 0.0f) // beta
	//		{
	//			m_angle_y = asinf(abs(m_norm_x)) * 180.0f / PI + 90.0f;
	//		}
	//		else if (m_norm_z >= 0.0f && m_norm_x <= 0.0f) // gamma
	//		{
	//			m_angle_y = asinf(m_norm_z) * 180.0f / PI + 180.0f;
	//		}
	//		else if (m_norm_z >= 0.0f && m_norm_x >= 0.0f) // phi
	//		{
	//			m_angle_y = 360.0f - acosf(m_norm_x) * 180.0f / PI;
	//		}
	//
	//		// Z rotation:
	//
	//		if (m_norm_y <= 0.0f && m_norm_x >= 0.0f) //alpha
	//		{
	//			m_angle_z = acosf(m_norm_x) * 180.0f / PI;
	//		}
	//		else if (m_norm_y <= 0.0f && m_norm_x <= 0.0f) // beta
	//		{
	//			m_angle_z = asinf(abs(m_norm_x)) * 180.0f / PI + 90.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_x <= 0.0f) // gamma
	//		{
	//			m_angle_z = asinf(m_norm_y) * 180.0f / PI + 180.0f;
	//		}
	//		else if (m_norm_y >= 0.0f && m_norm_x >= 0.0f) // phi
	//		{
	//			m_angle_z = 360.0f - acosf(m_norm_x) * 180.0f / PI;
	//		}
	//		m_logger << "Calculating angle OK. X rotation: " 
	//			<< m_angle_x << ";    Y rotation: " << m_angle_y << ";    Z rotation: " << m_angle_z;
	//	}
	//	//m_mtx.unlock();
	//}

}