#pragma once

namespace Ghurund::Engine::OpenGL {
	class OpenGLDrawingContext {
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::Engine::OpenGL::OpenGLDrawingContext>();
}