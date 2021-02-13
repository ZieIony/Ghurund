#pragma once

#include "ui/Orientation.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/ClickableControl.h"
#include "ui/layout/LinearLayout.h"

namespace Ghurund::UI {
    class Splitter:public ClickableControl {
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
        NONE, CHILD_1, CHILD_2
    };

    class SplitLayout:public ControlContainer {
    private:
        SharedPointer<Splitter> splitter;
        SharedPointer<ControlContainer> container1, container2;
        SharedPointer<LinearLayout> layout;
        LockedChild lockedChild = LockedChild::NONE;
        Orientation orientation;
        IntPoint pressMousePos = { 0,0 };

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

        void setChild1(Control* control);

        __declspec(property(get = getChild1, put = setChild1)) Control* Child1;

        inline Control* getChild2() {
            return container2->Child;
        }

        void setChild2(Control* control);

        __declspec(property(get = getChild2, put = setChild2)) Control* Child2;

        inline LockedChild getLockedChild() const {
            return lockedChild;
        }

        void setLockedChild(LockedChild child);

        __declspec(property(get = getLockedChild, put = setLockedChild)) LockedChild LockedChild;
    };

    typedef SharedPointer<SplitLayout> SplitLayoutPtr;
}