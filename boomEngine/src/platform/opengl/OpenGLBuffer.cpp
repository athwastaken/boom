#include "bmpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace bm {
	namespace draw {
		// vertex buffer
		OpenGLvertexBuffer::OpenGLvertexBuffer(float* vertices, uint32_t size) {
			glCreateBuffers(1, &m_drawID);
			glBindBuffer(GL_ARRAY_BUFFER, m_drawID);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}

		OpenGLvertexBuffer::~OpenGLvertexBuffer() {
			glDeleteBuffers(1, &m_drawID);
		}

		void OpenGLvertexBuffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_drawID);
		}
		
		void OpenGLvertexBuffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// index buffer
		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_count(count) {
			glCreateBuffers(1, &m_drawID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		}

		OpenGLIndexBuffer::~OpenGLIndexBuffer() {
			glDeleteBuffers(1, &m_drawID);
		}

		void OpenGLIndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawID);
		}

		void OpenGLIndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}