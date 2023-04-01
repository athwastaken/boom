#include "bmpch.h"
#include "shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace bm {
	namespace draw {
		shader::shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
			// Create an empty vertex shader handle
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = vertexSrc.c_str();
			glShaderSource(vertexShader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(vertexShader);

			GLint isCompiled = 0;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(vertexShader);

				BM_CORE_ERROR("{0}", infoLog.data());
				BM_CORE_ASSERT(false, "Vertex shader compilation failure.");
				return;
			}

			// Create an empty fragment shader handle
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			// Send the fragment shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			source = fragmentSrc.c_str();
			glShaderSource(fragmentShader, 1, &source, 0);

			// Compile the fragment shader
			glCompileShader(fragmentShader);

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(fragmentShader);
				// Either of them. Don't leak shaders.
				glDeleteShader(vertexShader);

				BM_CORE_ERROR("{0}", infoLog.data());
				BM_CORE_ASSERT(false, "Fragment shader compilation failure.");
				return;
			}

			// Vertex and fragment shaders are successfully compiled.
			// Now time to link them together into a program.
			// Get a program object.
			m_drawID = glCreateProgram();

			// Attach our shaders to our program
			glAttachShader(m_drawID, vertexShader);
			glAttachShader(m_drawID, fragmentShader);

			// Link our program
			glLinkProgram(m_drawID);

			// Note the different functions here: glGetProgram* instead of glGetShader*.
			GLint isLinked = 0;
			glGetProgramiv(m_drawID, GL_LINK_STATUS, (int*)&isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(m_drawID, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(m_drawID, maxLength, &maxLength, &infoLog[0]);

				// We don't need the program anymore.
				glDeleteProgram(m_drawID);
				// Don't leak shaders either.
				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);

				BM_CORE_ERROR("{0}", infoLog.data());
				BM_CORE_ASSERT(false, "Shader link failure");
				return;
			}

			// Always detach shaders after a successful link.
			glDetachShader(m_drawID, vertexShader);
			glDetachShader(m_drawID, fragmentShader);
		}

		shader::~shader() {
			glDeleteProgram(m_drawID);
		}

		void shader::bind() const {
			glUseProgram(m_drawID);
		}

		void shader::unbind() const {
			glUseProgram(0);
		}

		void shader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
			GLint location = glGetUniformLocation(m_drawID, name.c_str());
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
		}
	}
}