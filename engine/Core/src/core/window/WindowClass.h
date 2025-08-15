#pragma once

#include "core/string/String.h"
#include "core/window/WindowStyle.h"
#include "core/window/WindowProc.h"

namespace Ghurund::Core {
	class WindowClass {
	private:
		WindowStyle windowStyle;
		WNDPROC windowProc;
		String className = {};
		WNDCLASSEX windowClass = {};
		DWORD exStyle = {}, dwStyle = {};

		WindowClass(const WindowClass& other) = delete;

	public:
		WindowClass(WindowStyle style, WNDPROC windowProc = &Ghurund::Core::windowProc);

		inline void registerClass() {
			RegisterClassEx(&windowClass);
		}

		inline void unregisterClass() {
			UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		}

		HWND createWindow() const;

		void applyStyle(HWND handle) const;

		inline auto operator<=>(const WindowClass& other) const {
			if (windowProc == other.windowProc)
				return windowStyle <=> other.windowStyle;
			return (address_t)windowProc <=> (address_t)other.windowProc;
		}
	};
}