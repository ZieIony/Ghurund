#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class Space:public Control {
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        Space(float space = 8.0f) {}
    };
}