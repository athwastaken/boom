#include "bmpch.h"
#include "drawCommand.h"

#include "platform/OpenGL/OpenGLDrawAPI.h"

namespace bm {
	namespace draw {
		drawAPI* drawCommand::s_drawAPI = new OpenGLDrawAPI;
	}
}