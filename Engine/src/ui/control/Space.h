#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class Space :public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Space);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Space>();

    public:
        Space(float space = 8.0f) {
            preferredSize.width = PreferredSize::Width(space);
            preferredSize.height = PreferredSize::Height(space);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Space>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<Space> SpacePtr;
}