#pragma once

#include "core/collection/List.h"

namespace Ghurund::Core {
    class ApplicationWindow;

    class WindowCollection {
    private:
        List<ApplicationWindow*> windows;

		WindowCollection& operator=(const WindowCollection& other) = delete;

    public:
        ~WindowCollection() {
            clear();
        }

        inline void add(ApplicationWindow& window) {
            windows.add(&window);
        }

        inline void remove(ApplicationWindow& window) {
            windows.remove(&window);
        }

        inline void removeAt(size_t index) {
            windows.removeAt(index);
        }

        inline void clear() {
            windows.clear();
        }

        inline ArrayIterator<ApplicationWindow*> begin() {
            return windows.begin();
        }

        inline ConstArrayIterator<ApplicationWindow*> begin() const {
            return windows.begin();
        }

        inline ArrayIterator<ApplicationWindow*> end() {
            return windows.end();
        }

        inline ConstArrayIterator<ApplicationWindow*> end() const {
            return windows.end();
        }

        inline size_t getSize()const {
            return windows.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline ApplicationWindow& get(size_t i) const {
            return *windows.get(i);
        }

        inline size_t indexOf(ApplicationWindow& item) const {
            return windows.indexOf(&item);
        }

        inline bool contains(ApplicationWindow& item) const {
            return windows.contains(&item);
        }

        inline ApplicationWindow& operator[](size_t i) const {
            return *windows[i];
        }
    };
}