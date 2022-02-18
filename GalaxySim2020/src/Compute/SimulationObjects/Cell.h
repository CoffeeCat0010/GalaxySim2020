#pragma once
#include "Corepch.h"
#include "GravMass.h"
namespace Compute
{
	/// <summary>
	/// This is a Spactial Cell to be used for density gradients. Density was intended to be calculated
	/// as solar mass per parsec^3, however this is able to be used with any units. Note: it is the
	/// responsibility of the user to keep track of the units.
	/// </summary>
	class Cell
	{
	public: 
		Cell() : m_volume(1){}
		Cell (float dimXYZ)
			:m_masses(std::vector<GravMass>()), m_volume (dimXYZ* dimXYZ* dimXYZ), m_density(0){}
		inline void insertMass (GravMass& mass)
		{
			m_masses.push_back(mass);
			m_density += mass.mass / m_volume;
		}
		inline void clearCell ()
		{
			m_masses.clear();
			m_density = 0;
		}
		inline float getDensity ()
		{
			return m_density;
		}
	private:
		std::vector<GravMass> m_masses;
		float m_volume;
		float m_density;
	};
}