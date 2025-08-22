#pragma once

#include "engine/opengl/OglRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Ghurund::Engine;
using namespace Ghurund::Engine::OpenGL;

namespace UnitTest::Utils {
	class TestOglContext {
	private:
		OglRenderer* renderer;
		OglRenderingContext* context;
		SystemWindow* window;

	public:
		TestOglContext() {
			glfwInit();

			Timer timer;
			window = ghnew SystemWindow(timer);
			ParameterManager parameterManager;
			renderer = ghnew OglRenderer(parameterManager);
			renderer->init();
			context = renderer->makeRenderingContext(window);
			context->init();
			context->startFrame();

			glewInit();
		}

		~TestOglContext() {
			delete context;
			delete renderer;
			delete window;
			glfwTerminate();
		}
	};
}