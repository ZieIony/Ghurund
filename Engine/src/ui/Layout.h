#pragma once

#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "Control.h"
#include "core/collection/List.h"

namespace Ghurund {
    class Layout;

    class ChildrenList {
    private:
        List<Control*> children;
        Layout& owner;

    public:
        ChildrenList(Layout& owner):owner(owner) {}

        ~ChildrenList() {
            clear();
        }

        inline void add(Control* control) {
            children.add(control);
            control->Parent = &owner;
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

    class Layout:public Control {
    private:
        ChildrenList children;

    public:
        Layout():children(*this) {}

        void dispatchOnSizeChangedEvent() {
            for (Control* c : children) {

            }
        }

        virtual void setSize(float width, float height) override {
            Control::setSize(width, height);
            dispatchOnSizeChangedEvent();
        }

        ChildrenList& getChildren() {
            return children;
        }

        __declspec(property(get = getChildren)) ChildrenList& Children;

        virtual void draw()override {
            for (Control* c : children)
                c->draw();
        }

        virtual void layout() {
            for (Control* c : children)
                c->pos
        }
    };
}