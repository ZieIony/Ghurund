#pragma once

#include "WindowCloseAction.h"
#include "core/collection/List.h"
#include "core/window/SystemWindow.h"

namespace Ghurund::Core {
    class WindowList {
    private:
        List<SystemWindow*> windows;

        EventHandler<Window> destroyHandler = [this](Window& window) {
            remove((SystemWindow*)&window);
            delete& window;
            return true;
        };

        EventHandler<Window> hideHandler = [](Window& window) {
            window.Visible = false;
            return true;
        };

    public:
        ~WindowList() {
            clear();
        }

        inline void add(SystemWindow* window, WindowCloseAction action = WindowCloseAction::DESTROY) {
            windows.add(window);
            if (action == WindowCloseAction::DESTROY) {
                window->closed += destroyHandler;
            } else if (action == WindowCloseAction::HIDE) {
                window->closed += hideHandler;
            }
        }

        inline void remove(SystemWindow* window) {
            try {
                window->closed -= destroyHandler;
            } catch (...) {
                window->closed -= hideHandler;
            }
            windows.remove(window);
        }

        inline void removeAt(size_t index) {
            SystemWindow* window = windows.get(index);
            try {
                window->closed -= destroyHandler;
            } catch (...) {
                window->closed -= hideHandler;
            }
            windows.removeAt(index);
        }

        inline void clear() {
            for (SystemWindow* window : windows) {
                try {
                    window->closed -= destroyHandler;
                } catch (...) {
                    window->closed -= hideHandler;
                }
            }
            windows.clear();
        }

        inline ArrayIterator<SystemWindow*> begin() {
            return windows.begin();
        }

        inline ConstArrayIterator<SystemWindow*> begin() const {
            return windows.begin();
        }

        inline ArrayIterator<SystemWindow*> end() {
            return windows.end();
        }

        inline ConstArrayIterator<SystemWindow*> end() const {
            return windows.end();
        }

        inline size_t getSize()const {
            return windows.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline SystemWindow* get(size_t i)const {
            return windows.get(i);
        }

        inline size_t indexOf(SystemWindow* item) const {
            return windows.indexOf(item);
        }

        inline bool contains(SystemWindow* item) const {
            return windows.contains(item);
        }

        inline SystemWindow* operator[](size_t i)const {
            return windows[i];
        }
    };
}