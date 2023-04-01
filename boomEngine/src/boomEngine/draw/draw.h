#pragma once

#include "drawCommand.h"

#include "camera.h"
#include "shader.h"

namespace bm {
	namespace draw {
		class draw {
		public:
			static void beginScene(orthographicCamera& camera);
			static void endScene();

			static void submit(const ref<shader>& shader, const ref<vertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

			inline static drawAPI::API getAPI() { return drawAPI::getAPI(); }

		private:
			struct sceneData {
				glm::mat4 VPMatrix;
			};

			static sceneData* m_sceneData;
		};
	}
}