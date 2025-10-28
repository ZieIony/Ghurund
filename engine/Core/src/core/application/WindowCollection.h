#pragma once

#include "WindowCloseAction.h"
#include "core/collection/List.h"
#include "core/window/SystemWindow.h"

namespace Ghurund::Core {
    class WindowCollection {
    private:
        List<SystemWindow*> windows;

		WindowCollection& operator=(const WindowCollection& other) = delete;

    public:
        ~WindowCollection() {
            clear();
        }

        inline void add(SystemWindow& window) {
            windows.add(&window);
        }

        inline void remove(SystemWindow& window) {
            windows.remove(&window);
        }

        inline void removeAt(size_t index) {
            windows.removeAt(index);
        }

        inline void clear() {
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

        inline SystemWindow& get(size_t i) const {
            return *windows.get(i);
        }

        inline size_t indexOf(SystemWindow& item) const {
            return windows.indexOf(&item);
        }

        inline bool contains(SystemWindow& item) const {
            return windows.contains(&item);
        }

        inline SystemWindow& operator[](size_t i) const {
            return *windows[i];
        }
    };
}