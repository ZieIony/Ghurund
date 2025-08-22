#pragma once

#include <Windows.h>
#include <exception>

namespace Ghurund::Engine::DirectX {
	class DxCompilationException:public std::exception {
	private:
		HRESULT hr;

	public:
		DxCompilationException(HRESULT hr, const char* message):std::exception(message), hr(hr) {}

		HRESULT getResult() const {
			return hr;
		}

		__declspec(property(get = getResult)) HRESULT Result;
	};
}
