#pragma once

#include <exception>

namespace Ghurund::Engine::OpenGL {
	class OglCompilationException:public std::exception {
	public:
		OglCompilationException(const char* message):std::exception(message) {}
	};
}
