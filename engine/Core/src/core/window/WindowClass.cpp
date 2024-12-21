#include "ghcpch.h"
#include "WindowClass.h"

#include "SystemWindow.h"

namespace Ghurund::Core {
	void WindowClass::init() {
		exStyle = windowStyle.showOnTaskbar ? WS_EX_APPWINDOW : WS_EX_NOACTIVATE;
		dwStyle =
			(windowStyle.hasMinimizeButton ? WS_MINIMIZEBOX | WS_SYSMENU : 0) |
			(windowStyle.hasMaximizeButton ? WS_MAXIMIZEBOX | WS_SYSMENU : 0) |
			(windowStyle.hasTitle ? WS_CAPTION | WS_SYSMENU : 0) |
			(windowStyle.borderStyle == WindowBorderStyle::RESIZE ? WS_THICKFRAME : 0) |
			(windowStyle.borderStyle == WindowBorderStyle::THIN ? WS_BORDER : 0);

		this->className = std::format(_T("Ghurund{}{}{}{}{}{}{}"),
			windowStyle.hasMaximizeButton ? 1 : 0,
			windowStyle.hasMinimizeButton ? 1 : 0,
			windowStyle.hasTitle ? 1 : 0,
			(size_t)windowStyle.borderStyle,
			windowStyle.showOnTaskbar ? 1 : 0,
			windowStyle.hasShadow ? 1 : 0,
			*(address_t*)windowProc
		).c_str();

		UINT style = windowStyle.hasShadow ? CS_DROPSHADOW : 0;

		HINSTANCE hInst = GetModuleHandle(0);

		windowClass = {
			.cbSize = sizeof(WNDCLASSEX),
			.style = style, // OpenGL: .style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			.lpfnWndProc = windowProc,
			.cbClsExtra = 0L,
			.cbWndExtra = 0L,
			.hInstance = hInst,
			.hIcon = 0,
			.hCursor = nullptr,
			.hbrBackground = 0,
			.lpszMenuName = 0,
			.lpszClassName = this->className.Data,
			.hIconSm = 0
		};
	}

	HWND WindowClass::createWindow() const {
		return CreateWindowEx(exStyle, windowClass.lpszClassName, nullptr, dwStyle, 0, 0, 0, 0, nullptr, nullptr, windowClass.hInstance, nullptr);
	}

}