#pragma once

#include "ui/Orientation.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/ClickableView.h"
#include "ui/layout/LinearLayout.h"

namespace Ghurund::UI {
    class Splitter:public ClickableView {
    private:
        Orientation orientation;

    public:
        Splitter(Orientation orientation) {
            Orientation = orientation;
        }

        inline Orientation getOrientation() const {
            return orientation;
        }

        void setOrientation(Orientation orientation);

        __declspec(property(get = getOrientation, put = setOrientation)) Orientation Orientation;
    };

    enum class LockedChild {
        CHILD_1, CHILD_2
    };

    class SplitLayout:public ControlContainer {
    private:
        ScopedPointer<Splitter> splitter;
        ScopedPointer<ControlContainer> container1, container2;
        ScopedPointer<LinearLayout> layout;
        LockedChild lockedChild = LockedChild::CHILD_1;
        Orientation orientation;
        XMINT2 pressMousePos = { 0,0 };

    public:
        SplitLayout(Orientation orientation = Orientation::HORIZONTAL);

        inline Orientation getOrientation() const {
            return splitter->Orientation;
        }

        void setOrientation(Orientation orientation);

        __declspec(property(get = getOrientation, put = setOrientation)) Orientation Orientation;

        inline Control* getChild1() {
            return container1->Child;
        }

        inline void setChild1(Control* control) {
            container1->Child = control;
            if (control) {
                control->PreferredSize.width = PreferredSize::Width::FILL;
                control->PreferredSize.height = PreferredSize::Height::FILL;
            }
        }

        __declspec(property(get = getChild1, put = setChild1)) Control* Child1;

        inline Control* getChild2() {
            return container2->Child;
        }

        inline void setChild2(Control* control) {
            container2->Child = control;
            if (control) {
                control->PreferredSize.width = PreferredSize::Width::FILL;
                control->PreferredSize.height = PreferredSize::Height::FILL;
            }
        }

        __declspec(property(get = getChild2, put = setChild2)) Control* Child2;

        inline LockedChild getLockedChild() const {
            return lockedChild;
        }

        inline void setLockedChild(LockedChild child) {
            this->lockedChild = child;
        }

        __declspec(property(get = getLockedChild, put = setLockedChild)) LockedChild LockedChild;
    };

    typedef ScopedPointer<SplitLayout> SplitLayoutPtr;
}