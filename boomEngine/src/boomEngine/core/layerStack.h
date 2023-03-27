#pragma once

#include "base.h"
#include "layer.h"

#include <vector>

namespace bm {
	class layerStack
	{
	public:
		layerStack() = default;
		~layerStack();

		void pushLayer(layer* layer);
		void pushOverlay(layer* overlay);
		void popLayer(layer* layer);
		void popOverlay(layer* overlay);

		std::vector<layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<layer*>::iterator end() { return m_layers.end(); }
	private:
		std::vector<layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};
}