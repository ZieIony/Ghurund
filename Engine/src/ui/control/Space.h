#pragma once

#include "Control.h"

namespace Ghurund::UI {
    class Space:public Control {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Space))
                .withConstructor(NoArgsConstructor<Space>())
                .withSupertype(__super::TYPE);

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

    typedef ScopedPointer<Space> SpacePtr;

    inline SpacePtr makeSpace(float space = 8.0f) {
        return ScopedPointer<Space>(ghnew Space(space));
    }
}