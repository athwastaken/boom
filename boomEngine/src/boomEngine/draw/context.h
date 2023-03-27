#pragma once

namespace bm {
	namespace draw {
		class context {
		public:
			virtual void init() = 0;
			virtual void swapBuffers() = 0;
		};
	}
}