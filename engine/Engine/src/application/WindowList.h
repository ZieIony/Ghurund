#pragma once

#include "WindowCloseAction.h"
#include "application/ApplicationWindow.h"
#include "core/collection/List.h"

namespace Ghurund {
    class WindowList {
    private:
        List<ApplicationWindow*> windows;

        EventHandler<Window> destroyHandler = [this](Ghurund::Window& window) {
            remove((ApplicationWindow*)&window);
            delete& window;
            return true;
        };

        EventHandler<Window> hideHandler = [](Ghurund::Window& window) {
            window.Visible = false;
            return true;
        };

    public:
        ~WindowList() {
            clear();
        }

        inline void add(ApplicationWindow* window, WindowCloseAction action = WindowCloseAction::DESTROY) {
            windows.add(window);
            if (action == WindowCloseAction::DESTROY) {
                window->closed += destroyHandler;
            } else if (action == WindowCloseAction::HIDE) {
                window->closed += hideHandler;
            }
        }

        inline void remove(ApplicationWindow* window) {
            window->closed -= destroyHandler;
            window->closed -= hideHandler;
            windows.remove(window);
        }

        inline void removeAt(size_t index) {
            ApplicationWindow* window = windows.get(index);
            window->closed -= destroyHandler;
            window->closed -= hideHandler;
            windows.removeAt(index);
        }

        inline void clear() {
            for (ApplicationWindow* window : windows) {
                window->closed -= destroyHandler;
                window->closed -= hideHandler;
            }
            windows.clear();
        }

        inline ApplicationWindow** begin() {
            return windows.begin();
        }

        inline ApplicationWindow** begin() const {
            return windows.begin();
        }

        inline ApplicationWindow** end() {
            return windows.end();
        }

        inline ApplicationWindow** end() const {
            return windows.end();
        }

        inline size_t getSize()const {
            return windows.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline ApplicationWindow* get(size_t i)const {
            return windows.get(i);
        }

        inline size_t indexOf(ApplicationWindow* item) const {
            return windows.indexOf(item);
        }

        inline bool contains(ApplicationWindow* item) const {
            return windows.contains(item);
        }

        inline ApplicationWindow* operator[](size_t i)const {
            return windows[i];
        }
    };
}