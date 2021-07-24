#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
namespace Application
{
	// This is here mostly to decouple from the glm library. I want to limit use of glm in case I decide to change libraries.
	struct Vec2i
	{
		union
		{
			struct { int32_t x, y; };
			std::pair<int32_t, int32_t> component;
		};
	};
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

	inline Vec3f cl_float3ToVec3f (const cl_float3& vec)
	{
		return {vec.x, vec.y, vec.z};
	}

	inline std::shared_ptr<std::vector<Vec3f>> clFloatArrToVec3f (const cl_float3* arr, size_t numelements)
	{
		std::shared_ptr<std::vector<Vec3f>> result = std::make_shared<std::vector<Vec3f>>();
		result->reserve(numelements);
		for ( int i = 0; i < numelements; ++i )
			result->push_back({arr[i].x,	arr[i].y,	arr[i].z });
		return result;
	}
}