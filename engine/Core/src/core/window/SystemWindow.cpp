#include "ghcpch.h"
#include "SystemWindow.h"

#include "WindowClass.h"
#include "core/Timer.h"
#include "core/input/Input.h"
#include "core/reflection/TypeBuilder.h"

#include <shellapi.h>

namespace Ghurund::Core {
	const Ghurund::Core::Type& SystemWindow::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SystemWindow>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	HWND SystemWindow::makeWindow() {
		windowClass = makeShared<WindowClass>(Style, windowProc);
		windowClass->init();
		auto it = windowClassUses.find(windowClass);
		if (it == windowClassUses.end()) {
			windowClassUses.put(windowClass, 1);
			windowClass->registerClass();
		} else {
			windowClassUses[windowClass]++;
		}
		return windowClass->createWindow();
	}

	void SystemWindow::destroyWindow() {
		windowClassUses[windowClass]--;
		if (windowClassUses[windowClass] == 0) {
			windowClassUses.remove(windowClass);
			windowClass->unregisterClass();
		}
		DestroyWindow(Handle);
	}

	SystemWindow::~SystemWindow() {
		uninit();
	}

	void SystemWindow::init() {
		if (GetWindowLongPtr(handle, GWLP_USERDATA))
			return;

		handle = makeWindow();
		decorationMetrics.set(ghnew WindowDecorationMetrics(handle));
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)this);

		applySize();
		applyPosition();
		applyTitle();
		applyVisible();
	}

	void SystemWindow::uninit() {
		if (!GetWindowLongPtr(handle, GWLP_USERDATA))
			return;

		Visible = false;
		DragDropEnabled = false;

		decorationMetrics.set(nullptr);
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)nullptr);

		destroyWindow();
	}

	void SystemWindow::setVisible(bool visible) {
		if (Visible == visible)
			return;

		__super::setVisible(visible);
		applyVisible();
	}

	void SystemWindow::applyVisible() {
		if (!handle)
			return;

		ShowWindow(handle, Visible ? SW_SHOWNOACTIVATE : SW_HIDE);
	}

	void SystemWindow::setTitle(const String& title) {
		if (Title == title)
			return;

		__super::setTitle(title);
		applyTitle();
	}

	void SystemWindow::applyTitle() {
		if (!handle)
			return;

		SetWindowText(handle, Title.Data);
	}

	void SystemWindow::setPosition(const IntPoint& position) {
		if (Position == position)
			return;

		__super::setPosition(position);
		applyPosition();
	}

	void SystemWindow::applyPosition() {
		if (!handle)
			return;

		SetWindowPos(
			handle, 0,
			Position.x - decorationMetrics->Left, Position.y - decorationMetrics->Top,
			0, 0,
			SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE
		);
	}

	void SystemWindow::setSize(const IntSize& size) {
		if (Size == size)
			return;

		__super::setSize(size);
		applySize();
	}

	void SystemWindow::applySize() {
		if (!handle)
			return;

		SetWindowPos(
			handle, 0,
			0, 0,
			Size.Width + decorationMetrics->Horizontal, Size.Height + decorationMetrics->Vertical,
			SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE
		);
	}

	void SystemWindow::setDragDropEnabled(bool enabled) {
		if (DragDropEnabled == enabled)
			return;
		if (enabled) {
			dragDropManager.Swap(ghnew DragDropManager(*this));
			DragAcceptFiles(handle, TRUE);
			RegisterDragDrop(handle, dragDropManager.Get());
		} else {
			RevokeDragDrop(handle);
			DragAcceptFiles(handle, FALSE);
			dragDropManager.Reset();
		}
	}

	void SystemWindow::update(const uint64_t time) {
		input.dispatchEvents(time, *this);
	}

	void SystemWindow::dispatchMouseEvent(UINT msg, WPARAM wParam) {
		if (msg == WM_MOUSEMOVE) {
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(Handle, &p);
			input.addEvent({ msg, wParam, timer->TimeMs, p });

			if (!mouseTracked) {
				mouseTracked = true;

				TRACKMOUSEEVENT mouseEvt;
				ZeroMemory(&mouseEvt, sizeof(TRACKMOUSEEVENT));
				mouseEvt.cbSize = sizeof(TRACKMOUSEEVENT);
				mouseEvt.dwFlags = TME_LEAVE;
				mouseEvt.hwndTrack = Handle;
				TrackMouseEvent(&mouseEvt);
			}
		} else if (msg == WM_MOUSELEAVE) {
			mouseTracked = false;
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(Handle, &p);
			input.addEvent({ msg, wParam, timer->TimeMs, p });
		} else {
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(Handle, &p);
			input.addEvent({ msg, wParam, timer->TimeMs, p });
		}
	}

	bool SystemWindow::dispatchWindowEvent(UINT msg, WPARAM wParam, LPARAM lParam) {
		if (msg >= WM_KEYFIRST && msg <= WM_KEYLAST) {
			input.addEvent({ msg, wParam, timer->TimeMs });
			return true;
		} else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
			dispatchMouseEvent(msg, wParam);
			return true;
		} else if (msg == WM_WINDOWPOSCHANGED) {
			WINDOWPOS* windowPos = (WINDOWPOS*)lParam;

			RECT rc;
			GetWindowRect(handle, &rc);
			if (windowPos->flags ^ SWP_NOMOVE && (rc.left != windowPos->x || rc.top != windowPos->y)) {
				Position = { rc.left, rc.top };
				dispatchPositionChangedEvent();
			}
			auto newSize = IntSize(rc.right - rc.left, rc.bottom - rc.top);
			if (windowPos->flags ^ SWP_NOSIZE && (newSize.Width != windowPos->cx || newSize.Height != windowPos->cy)) {
				Size = newSize;
				dispatchSizeChangedEvent();
			}
			return true;   // already handled
		} else if (msg == WM_NCACTIVATE) {
			if (GetWindowLong(Handle, GWL_EXSTYLE) & WS_EX_NOACTIVATE && wParam == FALSE) {
				PostMessage(Handle, WM_CLOSE, 0, 0);
				return true;
			}
		} else if (msg == WM_SETFOCUS || msg == WM_KILLFOCUS) {
			dispatchFocusedChangedEvent();
			return true;
		} else if (msg == WM_CLOSE) {
			dispatchClosedEvent();
			return true;
		} else if (msg == WM_PAINT || msg == WM_ERASEBKGND) {
		  //  window.OnPaint();   // TODO: do it in the message loop
			return true;
		}
		return false;
	}
}