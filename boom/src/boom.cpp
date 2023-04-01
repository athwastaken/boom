#include <boomEngine.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <imgui.h>

class exampleLayer : public bm::layer {
public:
	exampleLayer() : layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f), m_cameraRotation(0.0f) {
		m_vertexArray.reset(bm::draw::vertexArray::create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.9f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.1f, 0.1f, 0.9f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.9f, 0.1f, 1.0f,
		};

		bm::ref<bm::draw::vertexBuffer> vertexBuffer;
		vertexBuffer.reset(bm::draw::vertexBuffer::create(vertices, sizeof(vertices)));

		bm::draw::bufferLayout layout = {
			{ bm::draw::shaderDataType::float3, "a_position" },
			{ bm::draw::shaderDataType::float4, "a_colour" }
		};

		vertexBuffer->setLayout(layout);
		m_vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		bm::ref<bm::draw::indexBuffer> indexBuffer;
		indexBuffer.reset(bm::draw::indexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->setIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_colour;

			uniform mat4 u_VPMatrix;
			uniform mat4 u_transform;

			out vec3 v_position;
			out vec4 v_colour;
			void main()
			{
				v_position = a_position;
				v_colour = a_colour;
				gl_Position = u_VPMatrix * u_transform * vec4(a_position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 o_colour;

			in vec3 v_position;
			in vec4 v_colour;
			void main()
			{
				o_colour = v_colour;
			}
		)";

		m_shader.reset(new bm::draw::shader(vertexSrc, fragmentSrc));
	}

	virtual void onUpdate(bm::timestep ts) override {
		
		if (bm::input::isKeyPressed(BM_KEY_A))
			m_cameraPosition.x -= m_cameraMoveSpeed * ts;

		else if (bm::input::isKeyPressed(BM_KEY_D))
			m_cameraPosition.x += m_cameraMoveSpeed * ts;

		if (bm::input::isKeyPressed(BM_KEY_W))
			m_cameraPosition.y += m_cameraMoveSpeed * ts;

		else if (bm::input::isKeyPressed(BM_KEY_S))
			m_cameraPosition.y -= m_cameraMoveSpeed * ts;

		if (bm::input::isKeyPressed(BM_KEY_LEFT))
			m_cameraRotation -= m_cameraMoveSpeed * ts;

		else if (bm::input::isKeyPressed(BM_KEY_RIGHT))
			m_cameraRotation += m_cameraMoveSpeed * ts;

		/*
		if (bm::input::isKeyPressed(BM_KEY_UP))
			m_cameraPosition.y += m_cameraMoveSpeed * ts;

		else if (bm::input::isKeyPressed(BM_KEY_DOWN))
			m_cameraPosition.y -= m_cameraMoveSpeed * ts;
		*/

		bm::draw::drawCommand::setClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		bm::draw::drawCommand::clear();


		m_camera.setPosition(m_cameraPosition);
		m_camera.setRotation(m_cameraRotation);

		bm::draw::draw::beginScene(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

		for (int i = 0; i < 5; i++) {
			glm::vec3 pos(i * 0.1f, i * 0.1f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(0.1f), pos) * scale;
			bm::draw::draw::submit(m_shader, m_vertexArray, transform);
	}
		bm::draw::draw::endScene();
	}

	virtual void onImGuiDraw() override {
		
	}

	virtual void onEvent(bm::eventClass & e) override {
		
	}

private:
	bm::ref<bm::draw::shader> m_shader;
	bm::ref<bm::draw::vertexArray> m_vertexArray;

	bm::draw::orthographicCamera m_camera;

	glm::vec3 m_cameraPosition;
	float m_cameraMoveSpeed = 5.0f;
	
	float m_cameraRotation;
	float m_cameraRotationSpeed = 45.0f;
};

class boomGame : public bm::app {

public:
	boomGame() {
		pushLayer(new exampleLayer());
	}

	~boomGame() {

	}
};

bm::app * bm::createApp() {
	return new boomGame();
}