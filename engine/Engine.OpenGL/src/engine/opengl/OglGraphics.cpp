#include "gheoglpch.h"
#include "OglGraphics.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Ghurund::Engine::OpenGL {
    const Ghurund::Core::Type& OglGraphics::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<OglGraphics>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
	
	void OglGraphics::uninitGraphics() {
		delete context;
		delete renderer;
		delete window;
		glfwTerminate();
	}
	
	void OglGraphics::onInit() {
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
}