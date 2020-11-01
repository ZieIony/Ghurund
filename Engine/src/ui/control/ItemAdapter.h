#pragma once

#include "Control.h"
#include "ControlPool.h"
#include "core/Object.h"

namespace Ghurund::UI {
    template<class T>
    class ControlFactory {
    public:
        virtual ~ControlFactory() {}

        virtual T* makeControl() const = 0;
    };

    template<class T, class ControlType>
    class ItemAdapter:public ControlFactory<ControlType> {
    private:
        ControlPool<ControlType> pool;

    public:
        virtual bool canHandleItem(const T& item, size_t position) const {
            return true;
        }

        virtual void bind(ControlType& control, const T& item, size_t position) const {}

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