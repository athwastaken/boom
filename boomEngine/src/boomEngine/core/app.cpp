#include "bmpch.h"

#include "app.h"

namespace bm {

	app* app::s_instance = nullptr;

	app::app() {
		BM_CORE_ASSERT(!s_instance, "App already exists.");
		s_instance = this;
		
		m_running = true;
		m_window = std::unique_ptr<window>(window::create());
		m_window->eventCallback(BM_BIND_EVENT_FN(app::onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
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
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			
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
