#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class Space:public Control {
    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        Space(float space = 8.0f) {
            preferredSize.width = PreferredSize::Width(space);
            preferredSize.height = PreferredSize::Height(space);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}