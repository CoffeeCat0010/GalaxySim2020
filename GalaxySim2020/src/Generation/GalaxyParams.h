#pragma once
#include "Corepch.h"
#include "Utility/Math/MVec.h"
namespace Physics
{
	struct GalaxyParams
	{
		enum propertyID{
			PosXID, PosYID, PosZID,
			RotXID, RotYID, RotZID,
			NumStarsID, StarMassID,
			HasCenterMassID, CenterMassID, 
			DiameterID
		};
		Util::Vec3f pos = {0.f, 0.f, 0.f};
		Util::Vec3f rotation = { 0.f, 0.f,0.f };
		bool RotInRads = false;

		uint64_t numStars = 0;
		/// <summary>
		/// In solar masses
		/// </summary>
		float starMass = 1.0;

		bool hasCenterMass = false;
		/// <summary>
		/// In solar masses
		/// </summary>
		float centerMass = 0.f;
		/// <summary>
		/// In parsecs
		/// </summary>
		float diameter = 0.f;
	};
}