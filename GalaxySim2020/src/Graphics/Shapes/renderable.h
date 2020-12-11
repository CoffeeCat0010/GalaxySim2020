#pragma once
#include "../Primatives/vertex.h"
#include "Graphics/Buffers/Texture2D.h"
#include <utility>
#include <vector>

namespace Graphics
{
	class renderable
	{
	private:
		uint32_t m_shaderProgramID;
	public:
		renderable(unsigned int shaderProgramID): m_shaderProgramID(shaderProgramID) {}

		unsigned int getShaderProgram() const { return m_shaderProgramID; }

		//size_t for the two following should be the number of elements in each array
		virtual std::pair<vertex*, size_t> getVertexData() = 0;
		virtual std::pair<uint32_t*, size_t> getIndexData() = 0;
		virtual std::vector<Texture2D*> getTextures() = 0;
		
		virtual void onUpdate() {};

	};
}