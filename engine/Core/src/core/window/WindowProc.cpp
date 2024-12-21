#include "ghcpch.h"
#include "WindowProc.h"

#include "SystemWindow.h"

namespace Ghurund::Core {
	LRESULT CALLBACK windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
		SystemWindow* window = (SystemWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);

		if (window && window->dispatchWindowEvent(msg, wParam, lParam))
			return 0;

		return DefWindowProc(handle, msg, wParam, lParam);
	}
}