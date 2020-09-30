#include "Vector2f.h"
namespace Math {
	float Vector2f::dotProduct(const Vector2f& other) {
		float x1 = this->getX();
		float x2 = other.getX();
		float y1 = this->getY();
		float y2 = other.getY();
		return x1 * x2 + y1 * y2;
	}

}