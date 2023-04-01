#include "bmpch.h"
#include "buffer.h"

#include "draw.h"
#include "platform/OpenGL/OpenGLBuffer.h"

namespace bm {
	namespace draw {
		vertexBuffer* vertexBuffer::create(float* vertices, uint32_t size) {
			switch (draw::getAPI())
			{
				case drawAPI::API::none:
					BM_CORE_ASSERT(false, "drawAPI::none is currently not supported.");
					return nullptr;
				case drawAPI::API::OpenGL:
					return new OpenGLvertexBuffer(vertices, size);
			}
			BM_CORE_ASSERT(false, "Unknown drawAPI.");
			return nullptr;
		}
		indexBuffer* indexBuffer::create(uint32_t* indices, uint32_t count) {
			switch (draw::getAPI())
			{
				case drawAPI::API::none:
					BM_CORE_ASSERT(false, "drawAPI::none is currently not supported.");
					return nullptr;
				case drawAPI::API::OpenGL:
					return new OpenGLIndexBuffer(indices, count);
			}
			BM_CORE_ASSERT(false, "Unknown drawAPI.");
			return nullptr;
		}
	}
}