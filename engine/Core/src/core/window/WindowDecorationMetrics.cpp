#include "ghcpch.h"

#include "WindowDecorationMetrics.h"

namespace Ghurund::Core {
	void WindowDecorationMetrics::init(HWND handle) {
		RECT rc = { 0, 0, 0, 0 };
		DWORD dwStyle = (DWORD)GetWindowLong(handle, GWL_STYLE);
		AdjustWindowRect(&rc, dwStyle, false);
		left = -rc.left;
		top = -rc.top;
		right = rc.right;
		bottom = rc.bottom;
	}
}
