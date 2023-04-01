#pragma once

#include <string>
#include <glm/glm.hpp>

namespace bm {
	namespace draw {
		class shader {
		public:
			shader(const std::string& vertexSrc, const std::string& fragmentSrc);
			~shader();

			void bind() const;
			void unbind() const;

			void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		private:
			uint32_t m_drawID;
		};
	}
}