#pragma once
#include "Corepch.h"
namespace Application
{
	// This is here mostly to decouple from the glm library. I want to limit use of glm in case I decide to change libraries.
	struct Vec2f
	{
		union
		{
			struct { float x, y; };
			struct { float s, t; };
			struct { float theta, rad; };
			std::pair<float, float> component;
		};
	};
	struct Vec3f
	{
		union
		{
			struct { float x, y, z; };
			struct { float s, t, p; };
			struct { float r, g, b; };
			struct { float theta, rad, h; }; // cylindrical coords
			//TODO: consider implementing 3d polar coords
		};
	};
	struct Vec4f
	{
		union
		{
			struct { float x, y, z, w; };
			struct { float s, t, p, q; };
			struct { float r, g, b, a; };
		};
	};
}