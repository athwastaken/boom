#include "bmpch.h"

#include "app.h"

namespace bm {

	app* app::s_instance = nullptr;

	app::app() {
		BM_CORE_ASSERT(!s_instance, "App already exists.");
		s_instance = this;
		
		m_running = true;
		m_window = std::unique_ptr<window>(window::create());
		m_window->setEventCallback(BM_BIND_EVENT_FN(app::onEvent));
			
		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	app::~app() {
	}

	void app::onEvent(eventClass& e) {
		eventDispatcher dispatcher(e);

		dispatcher.dispatchEvent<windowCloseEvent>(BM_BIND_EVENT_FN(app::onWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.m_handled)
				break;
		}
	}

	void app::pushLayer(layer* layer) {
		m_layerStack.pushLayer(layer);
	}

	void app::pushOverlay(layer* overlay) {
		m_layerStack.pushOverlay(overlay);
	}

	void app::run() {
		while (m_running) {
			glClearColor(0.05f, 0.05f, 0.05f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			// updates

			for (layer* layer : m_layerStack) {
				layer->onUpdate();
			}

			// rendering

			m_ImGuiLayer->begin();
			for (layer* layer : m_layerStack) {
				layer->onImGuiDraw();
			}
			m_ImGuiLayer->end();

			m_window->onUpdate();
		}
	}
	
	bool app::onWindowClose(windowCloseEvent& e)
	{
		m_running = false;
		return true;
	}
}
