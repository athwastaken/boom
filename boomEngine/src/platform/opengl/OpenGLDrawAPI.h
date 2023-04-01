#pragma once

#include "boomEngine/draw/drawAPI.h"

namespace bm {
	namespace draw {
		class OpenGLDrawAPI : public drawAPI {
		public:
			virtual void setClearColor(const glm::vec4& color) override;
			virtual void clear() override;

			virtual void drawIndexed(const ref<vertexArray>& vertexArray) override;
		};
	}
}