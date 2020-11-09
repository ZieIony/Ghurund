#pragma once

#include "SystemWindow.h"
#include "core/collection/List.h"

namespace Ghurund {
    class Application;

    class WindowList {
    private:
        List<SystemWindow*> windows;
        Application& owner;

    public:
        WindowList(Application& owner):owner(owner) {}

        ~WindowList() {
            clear();
        }

        inline void add(SystemWindow* window) {
            windows.add(window);
            window->Application = &owner;
        }

        inline void addAll(const std::initializer_list<SystemWindow*>& windows) {
            for (SystemWindow* window : windows) {
                this->windows.add(window);
                window->Application = &owner;
            }
        }

        inline void insert(size_t i, SystemWindow* window) {
            windows.insert(i, window);
            window->Application = &owner;
        }

        inline void remove(SystemWindow* window) {
            window->Application = nullptr;
            windows.remove(window);
        }

        inline void removeAt(size_t index) {
            SystemWindow* window = windows.get(index);
            window->Application = nullptr;
            windows.removeAt(index);
        }

        inline void clear() {
            for (SystemWindow* child : windows) {
                child->Application = nullptr;
            }
            windows.clear();
        }

        inline SystemWindow** begin() {
            return windows.begin();
        }

        inline SystemWindow** begin() const {
            return windows.begin();
        }

        inline SystemWindow** end() {
            return windows.end();
        }

        inline SystemWindow** end() const {
            return windows.end();
        }

        inline size_t getSize()const {
            return windows.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void set(size_t i, SystemWindow* e) {
            SystemWindow* window = windows[i];
            if (window == e)
                return;
            window->Application = nullptr;
            windows.set(i, e);
            window->Application = &owner;
        }

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