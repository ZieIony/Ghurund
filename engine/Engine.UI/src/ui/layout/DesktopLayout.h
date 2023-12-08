#pragma once

#include "ui/control/ControlGroup.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    class DesktopLayout:public ControlGroup {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DesktopLayout::GET_TYPE();
#pragma endregion
    };
}