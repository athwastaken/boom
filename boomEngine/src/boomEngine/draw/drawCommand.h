#pragma once

#include "drawAPI.h"

namespace bm {
	namespace draw {
		class drawCommand {
		public:
			inline static void setClearColor(const glm::vec4& color) { s_drawAPI->setClearColor(color); }
			inline static void clear() { s_drawAPI->clear(); }

			inline static void drawIndexed(const ref<vertexArray>& vertexArray) {
				s_drawAPI->drawIndexed(vertexArray);
			}
		private:
			static drawAPI* s_drawAPI;
		};
	}
}
