#include "bmpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace bm {

	static GLenum shaderDataTypeToOpenGLBaseType(draw::shaderDataType type) {
		switch (type) {
			case draw::shaderDataType::float1:	return GL_FLOAT;
			case draw::shaderDataType::float2:	return GL_FLOAT;
			case draw::shaderDataType::float3:	return GL_FLOAT;
			case draw::shaderDataType::float4:	return GL_FLOAT;
			case draw::shaderDataType::mat3:	return GL_FLOAT;
			case draw::shaderDataType::mat4:	return GL_FLOAT;
			case draw::shaderDataType::int1:	return GL_INT;
			case draw::shaderDataType::int2:	return GL_INT;
			case draw::shaderDataType::int3:	return GL_INT;
			case draw::shaderDataType::int4:	return GL_INT;
			case draw::shaderDataType::boolean:	return GL_BOOL;
		}

		BM_CORE_ASSERT(false, "Unknown shaderDataType.");
		return 0;
	};

	namespace draw {
		OpenGLVertexArray::OpenGLVertexArray() {
			glCreateVertexArrays(1, &m_drawID);
		}

		OpenGLVertexArray::~OpenGLVertexArray() {
			glDeleteVertexArrays(1, &m_drawID);
		}

		void OpenGLVertexArray::bind() const {
			glBindVertexArray(m_drawID);
		}

		void OpenGLVertexArray::unbind() const {
			glBindVertexArray(0);
		}

		void OpenGLVertexArray::addVertexBuffer(const ref<vertexBuffer>& vertexBuffer) {
			BM_CORE_ASSERT(vertexBuffer->getLayout().getElement().size(), "Vertex buffer has no layout.")

			glBindVertexArray(m_drawID);
			vertexBuffer->bind();

			uint32_t index = 0;
			const auto& layout = vertexBuffer->getLayout();
			for (const auto& element : layout) {
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					element.getComponentCount(),
					shaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.getStride(),
					(const void*)element.offset
				);
				index++;
			}

			m_vertexBuffers.push_back(vertexBuffer);
		}

		void OpenGLVertexArray::setIndexBuffer(const ref<indexBuffer>& indexBuffer) {
			glBindVertexArray(m_drawID);
			indexBuffer->bind();

			m_indexBuffer = indexBuffer;
		}
	}
}