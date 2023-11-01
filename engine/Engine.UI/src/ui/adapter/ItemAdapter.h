#pragma once

#include "ControlPool.h"

#include "ui/control/Control.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    template<class T, class ControlType>
    class ItemAdapter {
    private:
        ControlPool<ControlType> pool;

    public:
        virtual ~ItemAdapter() {}
   
        virtual ControlType* makeControl() const = 0;

        virtual void bind(ControlType& control, T& item, size_t position) const {}

        inline ControlType* getControl() {
            if (pool.Empty)
                return makeControl();
            return pool.getControl();
        }

        inline void recycleControl(ControlType* control) {
            pool.recycle(control);
        }
    };
}