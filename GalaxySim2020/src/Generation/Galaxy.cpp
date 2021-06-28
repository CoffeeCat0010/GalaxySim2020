#include "Corepch.h"
#include "Galaxy.h"
#include <random>
#include <ctime>
#include "glm/gtx/euler_angles.hpp"
namespace Physics
{
	Galaxy::Galaxy (int numStars, cl_float3 galaxyPos, glm::vec3 axisOfRotation, glm::vec3 velocity,float radius, float centerMass)
		:m_galaxyVelocity(velocity), m_starPos(std::vector<cl_float3>()), m_StarMasses (std::vector<float> ()), m_starVelocities (std::vector<cl_float3> ()),
		m_galaxyPos(galaxyPos), m_axisOfRotation(axisOfRotation), m_numStars(numStars), m_galaxyRadius(radius), m_centerMass(centerMass)
	{
		placeStars (axisOfRotation);
	}
	void Galaxy::placeStars (glm::vec3 axisOfRotation)
	{
		glm::mat4 translation = glm::translate (glm::vec3{ m_galaxyPos.x, m_galaxyPos.y, m_galaxyPos.z });
		glm::mat4 rotation = glm::eulerAngleYXZ (axisOfRotation.y, axisOfRotation.x, axisOfRotation.z );
		glm::mat4 transform = translation * rotation;

		glm::vec4 center1( 0.0f,  0.0f, 0.0f, 1.0f );
		//glm::vec4 center2(-5.0f,  5.0f, 0.0f, 1.0f );
		//glm::vec4 center3(-5.0f, -5.0f, 0.0f, 1.0f );
		//glm::vec4 center4( 5.0f, -5.0f, 0.0f, 1.0f );

		center1 = transform * center1;
		//center2 = transform * center2;
		//center3 = transform * center3;
		//center4 = transform * center4;

		// Place for point masses that contain most of the mass of the galaxy at the center.
		// This is to hopefully make the simulation merge the galaxyies over time
		m_starPos.emplace_back (cl_float3{ center1.x, center1.y, center1.z });
		//m_starPos.emplace_back (cl_float3{ center2.x, center2.y, center2.z });
		//m_starPos.emplace_back (cl_float3{ center3.x, center3.y, center3.z });
		//m_starPos.emplace_back (cl_float3{ center4.x, center4.y, center4.z });
		m_StarMasses.emplace_back (m_centerMass);
	/*	m_StarMasses.emplace_back (m_centerMass / 4);
		m_StarMasses.emplace_back (m_centerMass / 4);
		m_StarMasses.emplace_back (m_centerMass / 4);*/
		m_starVelocities.emplace_back (cl_float3{m_galaxyVelocity.x,m_galaxyVelocity.y,m_galaxyVelocity.z});
	//	calcOrbitalVelocity (rotation, center1, sqrt (50), 0);
		/*calcOrbitalVelocity (rotation, center2, sqrt (50), 1);
		calcOrbitalVelocity (rotation, center3, sqrt (50), 2);
		calcOrbitalVelocity (rotation, center4, sqrt (50), 3);*/

		std::default_random_engine generator(std::time(0));
		std::uniform_real_distribution<float> distribution (0.1f, m_galaxyRadius);
		for ( int i = 1; i < m_numStars; i++ ) {
			float distance = distribution (generator);
			std::uniform_real_distribution<float> xDistrbution (-distance, distance);
			float xComponent = xDistrbution (generator);
			float yComponent = sqrt ((distance * distance) - (xComponent * xComponent));
			std::uniform_int_distribution<int> posNeg(0, 1);
			yComponent = posNeg (generator) == 1 ? -yComponent : yComponent;
			glm::vec4 starPos (xComponent, yComponent, 0.0f, 1.0f);
			calcOrbitalVelocity (rotation, starPos, distance, i);
			starPos = transform * starPos;
			m_starPos.emplace_back (cl_float3{ starPos.x, starPos.y, starPos.z });
			m_StarMasses.emplace_back (1.f);
		}
	}
	void Galaxy::calcOrbitalVelocity (glm::mat4& rotation, glm::vec4& starPos, float dist, int element)
	{
		float velocity = sqrt ((G * m_centerMass) / dist);
		std::default_random_engine generator;
		std::normal_distribution<float> distribution (0.0f, velocity / dist);
		float velocityZ = distribution (generator);
		if ( velocityZ >= velocity ) {
			velocityZ = velocity;
		}
		float velocityXY = sqrt ((velocity * velocity) - (velocityZ * velocityZ));
		float xUnit = starPos.x / dist;
		float yUnit = starPos.y / dist;
		glm::vec4 velVec (-yUnit * velocityXY, xUnit * velocityXY, velocityZ, 1.0f);
		velVec = rotation * velVec;
		m_starVelocities.emplace_back( cl_float3{ velVec.x + m_galaxyVelocity.x, velVec.y + m_galaxyVelocity.y, velVec.z + m_galaxyVelocity.z });
	}
}
