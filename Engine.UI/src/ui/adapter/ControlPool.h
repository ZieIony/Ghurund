#pragma once

#include "ItemAdapter.h"
#include "core/collection/PointerList.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    template<class ControlType>
    class ControlPool {
    private:
        PointerList<ControlType*> pool;

    public:
        ~ControlPool() {
            for(ControlType* c:pool)
                c->release();
        }

        inline bool isEmpty() const {
            return pool.Empty;
        }

        __declspec(property(get = isEmpty)) bool Empty;

        ControlType* getControl() {
            ControlType* control = pool[pool.Size - 1];
            control->addReference();
            pool.removeAt(pool.Size - 1);
            return control;
        }

        void recycle(ControlType* c) {
            pool.add(c);
        }
    };
}