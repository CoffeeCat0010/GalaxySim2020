#pragma once
#include "Utility/Math/MVec.h"
namespace Compute{
	struct GravMass
	{
		Util::Vec3f pos;
		Util::Vec3f vel;
		// this is expected to have the units of solar mass
		float mass;
	};
}