#pragma once

#include "boomEngine/draw/buffer.h"

namespace bm {
	namespace draw {
		class OpenGLvertexBuffer : public vertexBuffer {
		public:
			OpenGLvertexBuffer(float* vertices, uint32_t size);
			virtual ~OpenGLvertexBuffer() override;

			virtual void bind() const override;
			virtual void unbind() const override;

			virtual const bufferLayout& getLayout() const override { return m_layout; }
			virtual void setLayout(const bufferLayout& layout) override { m_layout = layout; }
		private:
			uint32_t m_drawID;
			bufferLayout m_layout;
		};

		class OpenGLIndexBuffer : public indexBuffer {
		public:
			OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
			virtual ~OpenGLIndexBuffer() override;

			virtual void bind() const override;
			virtual void unbind() const override;

			virtual uint32_t getCount() const { return m_count; }
		private:
			uint32_t m_drawID;
			uint32_t m_count;
		};
	}
}