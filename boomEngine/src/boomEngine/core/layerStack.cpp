#include "bmpch.h"
#include "layerStack.h"

namespace bm {
	layerStack::~layerStack() {
		for (layer* layer : m_layers) {
			layer->onDetach();
			delete layer;
		}
	}

	void layerStack::pushLayer(layer* layer) {
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
		layer->onAttach();
	}

	void layerStack::pushOverlay(layer* overlay) {
		m_layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void layerStack::popLayer(layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
		if (it != m_layers.begin() + m_layerInsertIndex) {
			layer->onDetach();
			m_layers.erase(it);
			m_layerInsertIndex--;
		}
	}

	void layerStack::popOverlay(layer* overlay) {
		auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);
		if (it != m_layers.end()) {
			overlay->onDetach();
			m_layers.erase(it);
		}
	}
}
