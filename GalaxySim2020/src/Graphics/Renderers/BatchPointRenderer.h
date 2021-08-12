#pragma once
#include "Corepch.h"
#include "Graphics/Buffers/VertexArrayObj.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Shaders/ShaderProgram.h"

namespace Graphics
{
	class BatchPointRenderer
	{
	private:
		using batch = std::vector<glm::vec3>;
		enum Defaults
		{
			// about 4mb per batch
			DefaultVertsPerBatch = 262144,
		};
		const uint32_t m_maxVerts;
		VertexBuffer m_vertexBuf;
		VertexArrayObj_NoInd m_vao;
		uint32_t m_shaderProgramID;
		float m_aspectRatio;
		glm::mat4 projMatrix;
		std::list<batch*> m_batches;
		int projMatLocation;
	public:
		BatchPointRenderer (ShaderProgram& shader, float aspectRatio);
		BatchPointRenderer() = default;
		void addPoint(glm::vec3& point);
		void render();
		inline void setAspectratio(float ratio) 
		{
			m_aspectRatio = ratio;
			projMatrix = glm::perspective (glm::radians (90.0f), ratio, 0.1f, 10000.0f);
		}
	};
}

