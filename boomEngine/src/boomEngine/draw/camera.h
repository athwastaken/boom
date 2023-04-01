#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace bm {
	namespace draw {
		/*
		class camera {
		public:
			virtual ~camera() {};

			virtual const glm::vec3& getPosition() const = 0;
			virtual void setPosition(const glm::vec3& position) = 0;

			virtual float getRotation() const = 0;
			virtual void setRotation(float rotation) = 0;
			virtual const glm::mat4& getProjectionMatrix() const = 0;
			virtual const glm::mat4& getViewMatrix() const = 0;
			virtual const glm::mat4& getVPMatrix() const = 0;

		private:
			virtual void recalculateViewMatrix() = 0;
		};
		*/

		class orthographicCamera /*: public camera*/ {
		public:
			orthographicCamera(float left, float right, float bottom, float top);
			/*virtual*/ ~orthographicCamera() {};
			/*virtual*/ const glm::vec3& getPosition() const { return m_position; }
			/*virtual*/ void setPosition(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); }

			/*virtual*/ float getRotation() const { return m_rotation; }
			/*virtual*/ void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); }

			/*virtual*/ const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
			/*virtual*/ const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
			/*virtual*/ const glm::mat4& getVPMatrix() const { return m_VPMatrix; }
		private:
			/*virtual*/ void recalculateViewMatrix() /*override*/;

			glm::mat4 m_projectionMatrix;
			glm::mat4 m_viewMatrix;
			glm::mat4 m_VPMatrix;

			glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
			float m_rotation = 0.0f;
		};

		/*
		class perspectiveCamera : public camera {
		public:
			perspectiveCamera(float viewAngle, float aspect, float znear, float zfar);

			virtual ~perspectiveCamera() {};

			virtual const glm::vec3& getPosition() const { return m_position; }
			virtual void setPosition(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); }

			virtual glm::quat getRotation() const { return m_rotation; }
			virtual void setRotation(glm::quat rotation) {
				m_rotation = rotation; recalculateViewMatrix();
			}

			virtual const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
			virtual const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
			virtual const glm::mat4& getVPMatrix() const { return m_VPMatrix; }
		private:
			virtual void recalculateViewMatrix() override;

			glm::mat4 m_projectionMatrix;
			glm::mat4 m_viewMatrix;
			glm::mat4 m_VPMatrix;

			glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
			glm::quat m_rotation = { 0.0f, 0.0f, 0.0f, 0.0f };
		};
		*/
	}
}