#include "ghuipch.h"
#include "ColorAttr.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ColorAttr::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorAttr))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& ColorValue::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorValue))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& ColorRef::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorRef))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Color ColorRef::getValue(const Control& owner) const {
        return owner.Theme->Colors[key];
    }
}
