#include "BatchPointRenderer.h"

namespace Graphics
{
	BatchPointRenderer::BatchPointRenderer (ShaderProgram& shader, float aspectRatio = (16.0f / 9.0f))
	: m_maxVerts(DefaultVertsPerBatch), m_vertexBuf (VertexBuffer (0, sizeof (glm::vec3)* m_maxVerts)), 
		m_vao(&m_vertexBuf), m_shaderProgramID (shader.getID ()), 
		m_aspectRatio(aspectRatio),
		projMatrix (glm::perspective (glm::radians (90.0f), aspectRatio, 0.1f, 10000.0f))
	{
		m_vao.addAttrib (0, 3, sizeof (glm::vec3), 0);
		GL_CHECK (projMatLocation = glGetUniformLocation (m_shaderProgramID, "u_projMatrix"));
	}
	void BatchPointRenderer::addPoint (glm::vec3& point)
	{
		
		bool hasFoundBatch = false;
		bool hasRoomForVerts;
		for ( batch* b : m_batches )
		{
			hasRoomForVerts = m_maxVerts - (b->size() + 1) > 0;
			if (hasRoomForVerts)
			{
				hasFoundBatch = true;
				b->emplace_back(point);
			}
		}
		if ( !hasFoundBatch )
		{
			m_batches.emplace_front (new batch ());
			//todo think about writing a seperate helper function for the following section
			m_batches.front ()->reserve (m_maxVerts);
			m_batches.front ()->emplace_back(point);
		}
	}
	void BatchPointRenderer::render ()
	{
		GL_CHECK (glUseProgram (m_shaderProgramID));
		for ( batch* b : m_batches )
		{
			m_vao.bind ();
			m_vertexBuf.bind ();
			GL_CHECK (glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof (glm::vec3) * m_maxVerts, b->data ()));
	
			GL_CHECK (glUniformMatrix4fv (projMatLocation, 1, GL_FALSE, &projMatrix[0][0]));

			GL_CHECK (glDrawArrays (GL_POINTS, 0, b->size()));
			#pragma warning (default: 4267)
			b->clear ();
			delete b;
		}
		m_batches.clear ();
	}
}