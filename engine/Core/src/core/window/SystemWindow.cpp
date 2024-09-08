#include "ghcpch.h"
#include "SystemWindow.h"

#include "WindowClass.h"
#include "core/Timer.h"
#include "core/input/Input.h"
#include "core/reflection/TypeBuilder.h"

#include <time.h>
#include <shellapi.h>
#include <windowsx.h>

namespace Ghurund::Core {
    const Ghurund::Core::Type& SystemWindow::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SystemWindow>(NAMESPACE_NAME, GH_STRINGIFY(SystemWindow))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    SystemWindow::~SystemWindow() {
        if (!windowData)
            return;

        visible = false;
        DragDropEnabled = false;

        delete windowData;
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)nullptr);

        DestroyWindow(handle);
    }

    void SystemWindow::init(WindowManager& windowManager) {
        handle = windowManager.makeWindow(Style);
        windowData = ghnew WindowData(this);
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)windowData);

        title += [&](const WString& title) {
            SetWindowTextW(handle, title.Data);
        };
        size += [&](const IntSize& size) {
            dispatchSizeChangingEvent({ size.Width, size.Height });
            RECT rc, rcClient;
            GetWindowRect(handle, &rc);
            GetClientRect(handle, &rcClient);
            int xExtra = rc.right - rc.left - rcClient.right;
            int yExtra = rc.bottom - rc.top - rcClient.bottom;

            SetWindowPos(handle, 0, 0, 0, size.Width + xExtra, size.Height + yExtra, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
            dispatchSizeChangedEvent();
        };
        visible += [&](const bool& visible) {
            ShowWindow(handle, visible ? SW_SHOWNOACTIVATE : SW_HIDE);
        };
        position += [&](const IntPoint& position) {
            SetWindowPos(handle, 0, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
            dispatchPositionChangedEvent();
        };
    }

    void SystemWindow::setDragDropEnabled(bool enabled) {
        if (isDragDropEnabled() == enabled)
            return;
        if (enabled) {
            dragDropManager = ghnew DragDropManager(*this);
            DragAcceptFiles(handle, TRUE);
            RegisterDragDrop(handle, dragDropManager);
        } else {
            RevokeDragDrop(handle);
            DragAcceptFiles(handle, FALSE);
            if (dragDropManager) {
                dragDropManager->Release();
                dragDropManager = nullptr;
            }
        }
    }

    void SystemWindow::update(const uint64_t time) {
        input.dispatchEvents(time, *this);
    }
}