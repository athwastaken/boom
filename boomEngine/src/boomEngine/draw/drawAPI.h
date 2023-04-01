#pragma once

#include <glm/glm.hpp>
#include "vertexArray.h"

namespace bm {
	namespace draw {
		class drawAPI {
		public:
			enum class API {
				none = 0, OpenGL = 1
			};

			virtual void setClearColor(const glm::vec4& color) = 0;
			virtual void clear() = 0;
			virtual void drawIndexed(const ref<vertexArray>& vertexArray) = 0;
			
			inline static API getAPI() { return s_API; }
			
		private:
			inline static API s_API = drawAPI::API::OpenGL;
		};
	}
}