#include "Corepch.h"
#include "BatchRenderer.h"
#include <algorithm>
#include <limits>
#include "IO/GL_Logger.h"
#include "IO/Logger.h"

namespace Graphics
{
	int BatchRenderer::s_maxTextureUnits = -1;

	BatchRenderer::BatchRenderer (ShaderProgram& shader, bool allowTextures)
		:m_maxVerts (DEFAULT_MAX_VERTS), m_maxIndicies ((uint32_t)ceil (DEFAULT_INDEX_RATIO* DEFAULT_MAX_VERTS)),
		m_indexBuf (IndexBuffer (0, sizeof (uint32_t)* m_maxIndicies)), m_vertexBuf (VertexBuffer (0, sizeof (vertex)* m_maxVerts)),
		m_vao (VertexArrayObj (&m_vertexBuf, &m_indexBuf)), m_shaderProgramID (shader.getID ()), m_allowTextures (allowTextures),
		projMatrix (glm::perspective (glm::radians (90.0f), 16.0f / 9.0f, 0.1f, 10000.0f))
	{
		m_vao.addAttrib(0, 3, sizeof(vertex), (const void*)offsetof(vertex, m_pos));
		m_vao.addAttrib(1, 4, sizeof(vertex), (const void*)offsetof(vertex, m_color));
		m_vao.addAttrib(2, 2, sizeof(vertex), (const void*)offsetof(vertex, m_texCoords));
		m_vao.addAttrib(3, 1, sizeof(vertex), (const void*)offsetof(vertex, m_textureID), GL_INT);
		
	}
	
	BatchRenderer::BatchRenderer(ShaderProgram& shader, uint32_t maxVerts, float indexRatio, bool allowTextures)
		: m_maxVerts(maxVerts), m_maxIndicies((uint32_t)ceil(indexRatio * DEFAULT_MAX_VERTS)), m_indexBuf(IndexBuffer(nullptr, sizeof(uint32_t) * m_maxIndicies)),
		m_vertexBuf(VertexBuffer(nullptr, sizeof(vertex) * m_maxVerts)), m_vao(VertexArrayObj(&m_vertexBuf, &m_indexBuf)), m_shaderProgramID(shader.getID()),
		m_allowTextures(allowTextures), projMatrix (glm::perspective (glm::radians (45.0f), 16.0f / 9.0f, 0.1f, 100.0f))
	{
		m_vao.addAttrib(0, 3, sizeof(vertex), (const void*)offsetof(vertex, m_pos));
		m_vao.addAttrib(1, 4, sizeof(vertex), (const void*)offsetof(vertex, m_color));
		m_vao.addAttrib(2, 2, sizeof(vertex), (const void*)offsetof(vertex, m_texCoords));
		m_vao.addAttrib(3, 1, sizeof(vertex), (const void*)offsetof(vertex, m_textureID), GL_INT);
	}

	BatchRenderer::~BatchRenderer()
	{}
	
	int BatchRenderer::getMaxTextureUnits()
	{
		if (s_maxTextureUnits == -1)
		{
			GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &s_maxTextureUnits));
		}
		return s_maxTextureUnits;
	}
	void BatchRenderer::addMesh(renderable& mesh)
	{
		std::vector<vertex> vData = applyModelMatrix (mesh);
		std::pair<uint32_t*, size_t> iData = mesh.getIndexData();
		bool hasFoundBatch = false;
		bool hasRoomForVerts;
		bool hasRoomForIndicies;
		bool hasBinding;
		for (batch* b : batches)
		{
			hasRoomForVerts = m_maxVerts - (b->m_vertArrayIndexPtr + vData.size()) > 0;
			hasRoomForIndicies = m_maxIndicies - (b->m_indArrayIndexPtr + iData.second) > 0;
			hasBinding = hasTextureBinding(mesh, *b);
			if (hasRoomForIndicies && hasRoomForVerts && (canAddTextureBinding(mesh, *b) || hasBinding))
			{
				if (!hasBinding){ addTextureBinding(mesh, *b); }
				hasFoundBatch = true;
				b->m_vertices.insert(b->m_vertices.begin() + b->m_vertArrayIndexPtr, vData.data() , vData.data() + vData.size());

				for (auto it = b->m_vertices.begin() + b->m_vertArrayIndexPtr; it != b->m_vertices.begin() + b->m_vertArrayIndexPtr + vData.size(); ++it)
				{
					setVertexTextureBinding((*it), *b);
				}

				//offset indices so that they match the position of the vertices
				std::vector<uint32_t> newIndices;
				newIndices.reserve(iData.second);

				LOG_ERROR_IF("Index offset is larger than a 32bit integer! This should not happen! Make sure computer is not in flames!", b->m_vertArrayIndexPtr > std::numeric_limits<uint32_t>::max());
				#pragma warning(disable: 4267)
				offsetIndices(iData, newIndices, b->m_vertArrayIndexPtr);
				#pragma warning (default: 4267)
				
				// I start from the begin() iterator because I plan on reusing this vector. If I always appended to the end, the vector might keep on growing.
				// I also use an interger to specify an offset instead of saving an iterator because I will need the integer value when I render.
				b->m_indices.insert(b->m_indices.begin() + b->m_indArrayIndexPtr, newIndices.begin(), newIndices.end());
				b->m_vertArrayIndexPtr += vData.size();
				b->m_indArrayIndexPtr += iData.second;
			}
		}
		if (!hasFoundBatch)
		{
			batches.emplace_front(new batch());	
			//todo think about writing a seperate helper function for the following section
			batches.front()->m_vertices.reserve(m_maxVerts);
			batches.front()->m_indices.reserve(m_maxIndicies);

			addTextureBinding(mesh, *(batches.front()));


			batches.front()->m_vertices.insert(batches.front()->m_vertices.begin() + batches.front()->m_vertArrayIndexPtr, vData.data(), vData.data() + vData.size());
			
			for (auto it = batches.front()->m_vertices.begin(); it != batches.front()->m_vertices.begin() + vData.size(); ++it)
			{
				setVertexTextureBinding((*it), *(batches.front()));
			}
			//offset indices so that they match the position of the vertices
			std::vector<uint32_t> newIndices;
			newIndices.reserve(iData.second);
			
			LOG_ERROR_IF("Index offset is larger than a 32bit integer! This should not happen! Make sure computer is not in flames!", batches.front()->m_vertArrayIndexPtr > std::numeric_limits<uint32_t>::max());
			#pragma warning(disable: 4267)
			offsetIndices(iData, newIndices, batches.front()->m_vertArrayIndexPtr);
			#pragma warning (default: 4267)
			batches.front()->m_indices.insert(batches.front()->m_indices.begin() + batches.front()->m_indArrayIndexPtr, newIndices.begin(), newIndices.end());
			batches.front()->m_vertArrayIndexPtr += vData.size();
			batches.front()->m_indArrayIndexPtr += iData.second;
		}
	}
	
	void BatchRenderer::render()
	{
		GL_CHECK(glUseProgram(m_shaderProgramID));
		for (batch* b : batches)
		{
			m_vao.bind();
			m_vertexBuf.bind();
			GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex) * m_maxVerts, b->m_vertices.data()));
			m_indexBuf.bind();
			GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * m_maxIndicies, b->m_indices.data()));
			int slot = 1;
			// 256 is max slots allowed by shader.
			//todo create constant
			std::vector<int> slotsUsed(256, 0);
			auto start = b->m_textureBinding.begin ();
			for (auto it = ++start; it != b->m_textureBinding.end() && slot < 32; ++it)
			{
				it->second->bind(slot);
				slotsUsed[slot] = slot;
				slot++;
			}
			//todo consider error checking to make sure slotsUsed does not change size
			int texLocation = 0;
			int projMatLocation = 0;
			GL_CHECK(texLocation = glGetUniformLocation(m_shaderProgramID, "u_textures"));
			GL_CHECK(glUniform1iv(texLocation, 32, slotsUsed.data()));
			GL_CHECK (projMatLocation = glGetUniformLocation (m_shaderProgramID, "u_projMatrix"));
			GL_CHECK (glUniformMatrix4fv (projMatLocation, 1, GL_FALSE, &projMatrix[0][0]));



			LOG_ERROR_IF("Index offset is larger than a 32bit integer! This should not happen! Make sure computer is not in flames!", batches.front()->m_vertArrayIndexPtr > std::numeric_limits<uint32_t>::max());
			#pragma warning(disable: 4267)
			GL_CHECK(glDrawElements(GL_TRIANGLES, b->m_indArrayIndexPtr, GL_UNSIGNED_INT, NULL));
			#pragma warning (default: 4267)
			b->m_vertices.clear ();
			b->m_indices.clear();
			delete b;
		}
		batches.clear ();
	}

	void BatchRenderer::offsetIndices(const std::pair<uint32_t*, size_t> indexData, std::vector<uint32_t>& out, uint32_t offset)
	{
		for (int i = 0; i < indexData.second; i++)
		{
			out.emplace_back(indexData.first[i] + offset);
		}
	}

	void BatchRenderer::setVertexTextureBinding(vertex& vert, batch& batch)
	{
		auto texMapItor = batch.m_textureBinding.find(vert.m_textureID);
		int dist = std::distance(batch.m_textureBinding.begin(), texMapItor);
		vert.m_textureID = dist;
	}


	bool BatchRenderer::hasTextureBinding(renderable& mesh, batch& batch)
	{
		for (Texture2D* tex : mesh.getTextures())
		{
			if (batch.m_textureBinding.find(tex->getID()) == batch.m_textureBinding.end())
				return false;
		}
		return true;
	}
	
	bool BatchRenderer::canAddTextureBinding(renderable& mesh, batch& batch)
	{
		return ((getMaxTextureUnits() - 1) - batch.m_textureBinding.size() - mesh.getTextures().size()) > 0;
	}

	void BatchRenderer::addTextureBinding(renderable& mesh, batch& batch)
	{
		if ( batch.m_textureBinding.empty () ) {
			batch.m_textureBinding.insert ({ 0 , 0 });
		}
		for (Texture2D* tex : mesh.getTextures())
		{
			batch.m_textureBinding.insert({ tex->getID(), tex});
		}
	}

	std::vector<vertex> BatchRenderer::applyModelMatrix (renderable& mesh)
	{
		std::vector<vertex> data = std::vector<vertex> (mesh.getVertexData().first, mesh.getVertexData ().first + mesh.getVertexData ().second);
		glm::mat4 modelMat = mesh.getModelMatrix ();
		glm::vec4 result;
		for ( vertex &v : data ) {
			result = modelMat * glm::vec4(v.m_pos, 1.0f);
			v.m_pos.x = result.x;
			v.m_pos.y = result.y;
			v.m_pos.z = result.z;
		}
		return data;
	}

}
