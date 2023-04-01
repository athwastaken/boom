#include "bmpch.h"
#include "vertexArray.h"

#include "drawAPI.h"

#include "platform/OpenGL/OpenGLVertexArray.h"

namespace bm {
	namespace draw {
		vertexArray* vertexArray::create()
		{
			switch (drawAPI::getAPI())
			{
			case drawAPI::API::none:
				BM_CORE_ASSERT(false, "drawAPI::none is currently not supported.");
				return nullptr;
			case drawAPI::API::OpenGL:
				return new OpenGLVertexArray();
			}
			BM_CORE_ASSERT(false, "Unknown drawAPI.");
			return nullptr;
		}
	}
}