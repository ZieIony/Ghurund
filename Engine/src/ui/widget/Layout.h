#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {
    class WidgetLayout {
    private:
        Control* root = nullptr;

    protected:
        inline void setRoot(Control* control) {
            setPointer(root, control);
        }

    public:
        virtual ~WidgetLayout() = 0 {
            if (root)
                root->release();
        }

        virtual void init() {}

        inline Control* getRoot() {
            return root;
        }

        __declspec(property(get = getRoot, put = setRoot)) Control* Root;

        virtual void onThemeChanged(Control& control) {}

        virtual void onStateChanged(Control& control) {}
    };
}
