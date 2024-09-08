#pragma once

#include "core/string/String.h"

#include <exception>

namespace Ghurund::Engine::DirectX {
	class CompilationErrorException:public std::exception {
	private:
		AString message;

	public:
		CompilationErrorException() {}

		CompilationErrorException(const char* message):std::exception(message),message(message) {}

		const AString& getMessage() const {
			return message;
		}

		__declspec(property(get = getMessage)) const AString& Message;
	};
}