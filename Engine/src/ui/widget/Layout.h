#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {
    class Layout {
    protected:
        Control* root = nullptr;

    public:
        virtual ~Layout() = 0 {
            if (root)
                root->release();
        }

        virtual void init() {}

        Control* getRoot() {
            return root;
        }

        __declspec(property(get = getRoot)) Control* Root;

        virtual void onStateChanged(Control& control) {}
    };
}
