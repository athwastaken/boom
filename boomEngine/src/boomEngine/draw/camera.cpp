#include "bmpch.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace bm {
	namespace draw {
		orthographicCamera::orthographicCamera(float left, float right, float bottom, float top)
			: m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_viewMatrix(1.0f) {
			m_VPMatrix = m_projectionMatrix * m_viewMatrix;
		}

		void orthographicCamera::recalculateViewMatrix() {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
			m_viewMatrix = glm::inverse(transform);
			m_VPMatrix = m_projectionMatrix * m_viewMatrix;
		}

		/*
		perspectiveCamera::perspectiveCamera(float viewAngle, float aspect, float znear, float zfar)
			: m_projectionMatrix(glm::perspective(viewAngle, aspect, znear, zfar)), m_viewMatrix(1.0f) {
			m_VPMatrix = m_projectionMatrix * m_viewMatrix;
		}

		void perspectiveCamera::recalculateViewMatrix() {
			glm::mat4 transform = glm::mat4_cast(glm::inverse(m_rotation)) * glm::translate(glm::mat4(1.0f), m_position) * glm::mat4_cast(m_rotation);

			m_viewMatrix = glm::inverse(transform);
			m_VPMatrix = m_projectionMatrix * m_viewMatrix;
		}
		*/
	}
}