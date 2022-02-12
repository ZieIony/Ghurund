#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class Space:public Control {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        Space(float space = 8.0f) {
            preferredSize.width = PreferredSize::Width(space);
            preferredSize.height = PreferredSize::Height(space);
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}