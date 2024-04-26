#pragma once

#include "ui/control/Control.h"
#include "ui/layout/ControlWithConstraints.h"

namespace Ghurund::UI {
    class ControlProvider {
    public:
        virtual ~ControlProvider() = 0 {}
        
        virtual ArrayIterator<Control*> begin() = 0;

        virtual ConstArrayIterator<Control*> begin() const = 0;

        virtual ArrayIterator<Control*> end() = 0;

        virtual ConstArrayIterator<Control*> end() const = 0;

        virtual size_t getChildCount() const = 0;
        
        virtual Control* getChild(size_t index) = 0;
        
        virtual void releaseChild(Control* control, size_t index) {}
    };
}