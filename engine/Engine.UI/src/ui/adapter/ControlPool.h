#pragma once

#include "core/collection/List.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    class ControlPool {
    private:
        Map<size_t, List<Control*>> pool;

    public:
        ~ControlPool() {
            for (auto& pair : pool) {
                for (Control* c : pair.value)
                    c->release();
            }
        }

        inline bool isEmpty(size_t type) const {
			return !pool.contains(type) || pool[type].Empty;
        }

        Control* getControl(size_t type) {
            auto& list = pool[type];
            Control* control = list[list.Size - 1];
            list.removeAt(list.Size - 1);
            return control;
        }

        void recycle(Control* c, size_t type) {
            pool[type].add(c);
            c->addReference();
        }
    };
}