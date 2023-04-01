#pragma once

#include "boomEngine/core/base.h"
#include "buffer.h"

namespace bm {
	namespace draw {
		class vertexArray {
		public:
			virtual ~vertexArray() {};

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual void addVertexBuffer(const ref<vertexBuffer>& vertexBuffer) = 0;
			virtual void setIndexBuffer(const ref<indexBuffer>& indexBuffer) = 0;

			virtual const std::vector<ref<vertexBuffer>>& getvertexBuffers() const = 0;
			virtual const ref<indexBuffer>& getIndexBuffer() const = 0;

			static vertexArray* create();
		};
	}
}