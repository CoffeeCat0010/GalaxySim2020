#pragma once
#include "Corepch.h"
#include "CL/cl.hpp"

#define G 4.300E-03f// (pc/solarMass) * (km/s)^2 
#define KM_PER_PARSEC 3.086E+13f

#define AVRG_GALAXY_RADIUS 1.25E04f //in Parsecs
#define DEFAULT_CENTER_MASS 1.5E9f // in solar masses

namespace Physics
{
	class Galaxy
	{
	private:
		std::vector<cl_float3> m_starPos;
		std::vector<float> m_StarMasses;
		std::vector<cl_float3> m_starVelocities;
		//TODO: change to Util::vec3f
		cl_float3 m_galaxyPos;
		glm::vec3 m_axisOfRotation;
		glm::vec3 m_galaxyVelocity;

		int m_numStars = 0;
		float m_galaxyRadius;
		float m_centerMass;
	public:
		Galaxy () = default;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="numStars"> Must be greater than or equal to 4. Otherwise it is undefined behavior. </param>
		/// <param name="galaxyPos"></param>
		/// <param name="axisOfRotation">The axis that the galaxy rotates around. This will spin in accordence with the right-hand rule</param>
		/// <param name="radius"></param>
		/// <param name="centerMass"></param>
		Galaxy (int numStars, cl_float3 galaxyPos, glm::vec3 axisOfRotation, glm::vec3 velocity,float radius = AVRG_GALAXY_RADIUS, float centerMass = DEFAULT_CENTER_MASS);

		std::vector<cl_float3>& getStarPos ()  { return m_starPos; }
		std::vector<float>& getStarMasses ()  { return m_StarMasses; }
		std::vector<cl_float3>& getStarVelocities ()  { return m_starVelocities; }
	private:

		void placeStars (glm::vec3 axisOfRotation);
		/// <summary>
		/// Takes the star position array and set the velocity array. 
		/// </summary>
		/// <param name="axisOfRotation">The axis that the galaxy rotates around. This will spin in accordence with the right-hand rule</param>
		void calcOrbitalVelocity (glm::mat4& rotation, glm::vec4& starPos, float dist, int element);

	};
}

