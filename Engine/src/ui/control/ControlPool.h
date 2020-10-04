#pragma once

#include "Control.h"
#include "ItemAdapter.h"
#include "core/collection/PointerList.h"

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

        ControlType* getControl(const ControlFactory<ControlType>& adapter) {
            if (pool.Empty)
                return adapter.makeControl();
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