#pragma once

#include "boomEngine/draw/vertexArray.h"

namespace bm {
	namespace draw {
		class OpenGLVertexArray : public vertexArray {
		public:
			OpenGLVertexArray();
			virtual ~OpenGLVertexArray();

			virtual void bind() const override;
			virtual void unbind() const override;

			virtual void addVertexBuffer(const ref<vertexBuffer>& vertexBuffer) override;
			virtual void setIndexBuffer(const ref<indexBuffer>& indexBuffer) override;

			virtual const std::vector<ref<vertexBuffer>>& getvertexBuffers() const { return m_vertexBuffers; }
			virtual const ref<indexBuffer>& getIndexBuffer() const { return m_indexBuffer; }

		private:
			uint32_t m_drawID;
			std::vector<ref<vertexBuffer>> m_vertexBuffers;
			ref<indexBuffer> m_indexBuffer;
		};
	}
}
