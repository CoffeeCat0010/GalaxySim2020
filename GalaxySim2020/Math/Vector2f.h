#pragma once
namespace Math {
	class Vector2f
	{
	private:
		float m_x, m_y;
	public:
		inline Vector2f(const float& x, const float& y) : m_x(x), m_y(y) {};
		inline void setX(const float& x) { m_x = x; };
		inline void setY(const float& y) { m_y = y; };
		inline float getX() const { return m_x; };
		inline float getY() const { return m_y; };
		float dotProduct(const Vector2f& other);
		inline float operator*(const Vector2f& other) { return dotProduct(other); };
	};
}

