#pragma once
#include "../Primatives/vertex.h"
#include <utility>

namespace Graphics
{
	class renderable
	{
	private:
		uint32_t m_shaderProgramID;
	public:
		renderable(unsigned int shaderProgramID): m_shaderProgramID(shaderProgramID) {}

		unsigned int getShaderProgram() { return m_shaderProgramID; }

		//size_t for the two following should be the number of elements in each array
		virtual std::pair<vertex*, size_t> getVertexData() = 0;
		virtual std::pair<unsigned int*, size_t> getIndexData() = 0;
		
		virtual void onUpdate() {};

	};
}