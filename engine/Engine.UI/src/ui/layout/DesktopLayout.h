#pragma once

#include "ui/control/ControlGroup.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    class DesktopLayout:public ControlGroup {
    private:
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}