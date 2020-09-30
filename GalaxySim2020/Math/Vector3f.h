#pragma once
namespace Math {
	class Vector3f
	{
	private:
		float m_x, m_y, m_z;
	public:
		inline Vector3f(const float& x, const float& y, const float& z) : m_x(x), m_y(y), m_z(z) {};
		inline void setX(const float& x) { m_x = x; };
		inline void setY(const float& y) { m_y = y; };
		inline void setZ(const float& z) { m_z = z; };
		inline float getX() const { return m_x; };
		inline float getY() const { return m_y; };
		inline float getZ() const { return m_z; };
		float dotProduct(const Vector3f& other);
		inline float operator*(const Vector3f& other) { return dotProduct(other); };
		Vector3f cross(const Vector3f& other);
	};
}

