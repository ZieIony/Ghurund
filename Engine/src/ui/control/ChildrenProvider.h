#pragma once

#include "ControlGroup.h"

namespace Ghurund::UI {
    __interface ChildrenProvider {
        virtual size_t getChildCount() const = 0;
        virtual Control* getChild(size_t index) = 0;
        virtual void releaseChild(Control* control, size_t index) = 0;
    };

    class ListChildrenProvider:public ChildrenProvider {
    private:
        ControlGroup& owner;

    public:
        ListChildrenProvider(ControlGroup& owner):owner(owner) {}

        virtual size_t getChildCount() const override {
            return owner.Children.Size;
        }

        virtual Control* getChild(size_t index) {
            return owner.Children[index];
        }

        virtual void releaseChild(Control* control, size_t index) {}
    };
}