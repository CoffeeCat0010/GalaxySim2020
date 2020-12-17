#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics
{
	class Camera
	{
	private:
		glm::vec3 pos;
		glm::vec3 viewPos;
		glm::mat4 view;
		glm::mat4 projection;
	public:
		Camera();
		~Camera();

		void setPos(glm::vec3& pos);
		void setPos(float x, float y, float z);

		void translate(glm::vec3& vec);
		void translate(float x, float y, float z);

		glm::vec3 getPos();



	};
}

