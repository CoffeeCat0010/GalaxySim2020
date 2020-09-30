#include "Vector3f.h"
namespace Math {
	float Vector3f::dotProduct(const Vector3f& other) {
		float x1 = this->getX();
		float x2 = other.getX();
		float y1 = this->getY();
		float y2 = other.getY();
		float z1 = this->getZ();
		float z2 = other.getZ();
		return x1 * x2 + y1 * y2 + z1 * z2;
	}

	Vector3f Vector3f::cross(const Vector3f& other) {
		float x1 = this->getX();
		float x2 = other.getX();
		float y1 = this->getY();
		float y2 = other.getY();
		float z1 = this->getZ();
		float z2 = other.getZ();

		float r_x = (y1 * z2) - (z1 * y2);
		float r_y = (z1 * x2) - (x1 * z2);
		float r_z = (x1 * y2) - (y1 * x2);
		return Vector3f(r_x, r_y, r_z);
	}
}