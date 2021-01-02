#pragma once

#include "ControlParent.h"
#include "core/collection/PointerList.h"

namespace Ghurund::UI {
    class ChildrenList {
    private:
        PointerList<Control*> children;
        ControlParent& owner;

    public:
        ChildrenList(ControlParent& owner):owner(owner) {}

        ~ChildrenList() {
            clear();
        }

        inline void add(Control* control) {
            children.add(control);
            control->Parent = &owner;
        }

        inline void addAll(const PointerList<Control*>& controls) {
            for (Control* control : controls) {
                children.add(control);
                control->Parent = &owner;
            }
        }

        inline void addAll(const std::initializer_list<Control*>& controls) {
            for (Control* control : controls) {
                children.add(control);
                control->Parent = &owner;
            }
        }

        inline void insert(size_t i, Control* control) {
            children.insert(i, control);
            control->Parent = &owner;
        }

        inline void remove(Control* control) {
            control->clearFocus();
            control->Parent = nullptr;
            children.remove(control);
        }

        inline void removeAt(size_t index) {
            Control* control = children.get(index);
            control->clearFocus();
            control->Parent = nullptr;
            children.removeAt(index);
        }

        inline void clear() {
            for (Control* child : children) {
                child->clearFocus();
                child->Parent = nullptr;
            }
            children.clear();
        }

        inline Control** begin() {
            return children.begin();
        }

        inline Control** begin() const {
            return children.begin();
        }

        inline Control** end() {
            return children.end();
        }

        inline Control** end() const {
            return children.end();
        }

        inline size_t getSize()const {
            return children.getSize();
        }

        __declspec(property(get = getSize)) size_t Size;

        inline void set(size_t i, Control* e) {
            Control* control = children[i];
            if (control == e)
                return;
            control->clearFocus();
            control->Parent = nullptr;
            children.set(i, e);
            control->Parent = &owner;
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