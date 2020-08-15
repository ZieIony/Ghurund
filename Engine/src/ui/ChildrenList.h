#pragma once

#include "Control.h"
#include "core/collection/PointerList.h"

namespace Ghurund::UI {
    class ChildrenList {
    private:
        PointerList<Control*> children;
        Control& owner;

    public:
        ChildrenList(Control& owner):owner(owner) {}

        ~ChildrenList() {
            clear();
        }

        inline void add(Control* control) {
            children.add(control);
            control->Parent = &owner;
        }

        inline void add(std::initializer_list<Control*> controls) {
            for (Control* control : controls) {
                children.add(control);
                control->Parent = &owner;
            }
        }

        inline void insert(size_t i, Control* control) {
            children.insertKeepOrder(i, control);
            control->Parent = &owner;
        }

        inline void remove(Control* control) {
            control->Parent = nullptr;
            children.removeKeepOrder(control);
        }

        inline void removeAt(size_t index) {
            children.get(index)->Parent = nullptr;
            children.removeAtKeepOrder(index);
        }

        inline void clear() {
            for (Control* child : children)
                child->Parent = nullptr;
            children.clear();
        }

        inline Control** begin() {
            return children.begin();
        }

        inline Control** end() {
            return children.end();
        }

        inline size_t getSize()const {
            return children.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void set(size_t i, Control* e) {
            children.set(i, e);
        }

        inline Control* get(size_t i)const {
            return children.get(i);
        }

        inline size_t indexOf(Control* item) const {
            return children.indexOf(item);
        }

        inline bool contains(Control* item) const {
            return children.contains(item);
        }

        inline Control* operator[](size_t i)const {
            return children[i];
        }
    };
}