#pragma once

#include "ui/control/ControlContainer.h"

namespace Ghurund::UI {
    class WidgetLayout {
    private:
        Control* root = nullptr;

    protected:
        inline void setRoot(Control* control) {
            setPointer(root, control);
        }

    public:
        WidgetLayout() {}

        WidgetLayout(Control* control) {
            root = control;
            root->addReference();
        }

        virtual ~WidgetLayout() = 0 {
            if (root)
                root->release();
        }

        inline Control* getRoot() {
            return root;
        }

        __declspec(property(get = getRoot, put = setRoot)) Control* Root;

        virtual void onThemeChanged(Control& control) {}

        virtual void onStateChanged(Control& control) {}
    };

    class ContainerLayout:public WidgetLayout {
    private:
        ControlContainer* container = nullptr;

        inline void setContainer(ControlContainer* container) {
            this->container = container;
        }

    public:
        ContainerLayout() {}

        ContainerLayout(Control* control):WidgetLayout(control) {
            container = (ControlContainer*)control->find("container");
        }

        inline ControlContainer* getContainer() {
            return container;
        }

        __declspec(property(get = getContainer)) ControlContainer* Container;
    };
}
