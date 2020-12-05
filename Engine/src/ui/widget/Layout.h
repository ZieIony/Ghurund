#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {
    class WidgetLayout {
    protected:
        Control* root = nullptr;

    public:
        virtual ~WidgetLayout() = 0 {
            if (root)
                root->release();
        }

        virtual void init() {}

        Control* getRoot() {
            return root;
        }

        __declspec(property(get = getRoot)) Control* Root;

        virtual void onThemeChanged(Control& control) {}

        virtual void onStateChanged(Control& control) {}
    };
}
