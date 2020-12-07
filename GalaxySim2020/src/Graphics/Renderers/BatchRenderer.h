#pragma once
#include <list>
#include "../Graphics/Primatives/vertex.h"
#include "../Graphics/Shapes/renderable.h"
#include "../Graphics/Buffers/VertexArrayObj.h"
#include "../Graphics/Buffers/IndexBuffer.h"
#include "../Graphics/Buffers/VertexBuffer.h"

namespace Graphics
{
	struct batch {
		vertex* m_vertices = nullptr;
		uint32_t* m_indices = nullptr;
	};
#define DEFAULT_MAX_VERTS 20000
	class BatchRenderer
	{
	private:
		//vertex data to be stored until sent to gpu
		std::list<batch*> batches;
		IndexBuffer m_indexBuf;
		VertexBuffer m_vertexBuf;
		VertexArrayObj m_vao;
		uint32_t m_shaderProgramID;
		const uint32_t m_maxVerts;
	public:
		BatchRenderer();
		BatchRenderer(uint32_t maxVerts);
		~BatchRenderer();
		void addMesh(renderable mesh);
		void render();

	private:
		inline bool hasSameShader(renderable mesh) { return mesh.getShaderProgram() == m_shaderProgramID; }

	};
}

