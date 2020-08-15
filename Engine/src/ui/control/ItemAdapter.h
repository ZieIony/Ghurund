#pragma once

#include "Control.h"
#include "core/Object.h"

namespace Ghurund::UI {
    template<class T>
    class ItemAdapter {
    public:
        virtual bool filter(const T& item)const {
            return true;
        }

        virtual Control* makeControl()const = 0;

        virtual void bind(const T& item, Control& control) const {}
    };
}