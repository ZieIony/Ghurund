#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class Space:public Control {
    private:
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<Space>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Space))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

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