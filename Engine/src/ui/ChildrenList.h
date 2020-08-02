#pragma once

#include "Control.h"
#include "core/collection/PointerList.h"

namespace Ghurund {
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

        inline  void remove(Control* control) {
            children.removeKeepOrder(control);
            control->Parent = nullptr;
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
    };
}