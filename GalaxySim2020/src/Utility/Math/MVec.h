#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"
#include "glm/glm.hpp"
namespace Util
{
	// This is here mostly to decouple from the glm library. I want to limit use of glm in case I decide to change libraries.

	/// <summary>
	/// Vec2i holds 2 int values
	/// </summary>
	struct Vec2i
	{
		union
		{
			struct { int32_t x, y; };
			//std::pair<int32_t, int32_t> component;
		};
	};
	/// <summary>
	/// Vec2f holds 2 float values
	/// </summary>
	struct Vec2f
	{
		union
		{
			struct { float x, y; };
			struct { float s, t; };
			struct { float theta, rad; };
			//std::pair<float, float> component;
		};
	};
	/// <summary>
	/// Vec3f holds 3 float values
	/// </summary>
	struct Vec3f
	{
		union
		{
			struct { float x, y, z; };
			struct { float s, t, p; };
			struct { float r, g, b; };
			struct { float theta, rad, h; }; // cylindrical coords
			//TODO: consider implementing 3d polar coords
			//Warning: __has_include() will not work with vs2013 or below and may not work with vs2015
		};
			#ifdef __has_include("glm.hpp")
			operator glm::vec3 () const { return { x, y, z }; };
			operator glm::vec4 () const { return {x, y, z, 0};};
			#endif
	};

	/// <summary>
/// Vec3i holds 3 int values
/// </summary>
	struct Vec3i
	{
		union
		{
			struct { int x, y, z; };
			struct { int r, g, b; };
			//Warning: __has_include() will not work with vs2013 or below and may not work with vs2015
		};
		#ifdef __has_include("glm.hpp")
		operator glm::vec3 () const { return { x, y, z }; };
		operator glm::vec4 () const { return { x, y, z, 0 }; };
		#endif
	};
	/// <summary>
	/// Vec4f holds 4 float values
	/// </summary>
	/// 
	struct Vec4f
	{
		union
		{
			struct { float x, y, z, w; };
			struct { float s, t, p, q; };
			struct { float r, g, b, a; };
		};
		#ifdef __has_include("glm.hpp")
		operator glm::vec4 () const { return { x, y, z, w }; };
		#endif
	};
	/// <summary>
	/// Converts a cl_float3 from OpenCL to a Vec3f
	/// </summary>
	/// <param name="vec">The cl_float3 being converted </param>
	/// <returns>Returns a Vec3f with the equivalent component values.</returns>
	inline Vec3f cl_float3ToVec3f (const cl_float3& vec)
	{
		return {vec.x, vec.y, vec.z};
	}
	/// <summary>
	/// Returns a Vec3f with the equivalent component values.
	/// </summary>
	/// <param name="arr"> Returns a Vec3f with the equivalent component values.</param>
	/// <param name="numElements"> The number of elements in the inputted array</param>
	/// <returns>Returns a vector equivalent to the cl_float3 array </returns>
	inline std::vector<Vec3f> clFloatArrToVec3f (const cl_float3* arr, size_t numElements)
	{
		std::vector<Vec3f> result;
		result.reserve (numElements);
		for ( int i = 0; i < numElements; ++i )
			result.push_back ({ arr[i].x,	arr[i].y,	arr[i].z });
		return result;
	}
}