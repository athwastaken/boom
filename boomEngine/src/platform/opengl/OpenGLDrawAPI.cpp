#include "bmpch.h"
#include "OpenGLDrawAPI.h"

#include <glad/glad.h>

namespace bm {
	namespace draw {
		void OpenGLDrawAPI::setClearColor(const glm::vec4& color) {
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void OpenGLDrawAPI::clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OpenGLDrawAPI::drawIndexed(const ref<vertexArray>& vertexArray) {
			glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}