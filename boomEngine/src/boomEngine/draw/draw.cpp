#include "bmpch.h"
#include "draw.h"

namespace bm {
	namespace draw {
		draw::sceneData* draw::m_sceneData = new draw::sceneData;

		void draw::beginScene(orthographicCamera& camera) {
			m_sceneData->VPMatrix = camera.getVPMatrix();
		}

		void draw::endScene() {
		}

		void draw::submit(const ref<shader>& shader, const ref<vertexArray>& vertexArray, const glm::mat4& transform) {
			shader->bind();
			shader->uploadUniformMat4("u_VPMatrix", m_sceneData->VPMatrix);
			shader->uploadUniformMat4("u_transform", transform);

			vertexArray->bind();
			drawCommand::drawIndexed(vertexArray);
		}
	}
}