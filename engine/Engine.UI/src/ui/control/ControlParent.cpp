#include "ghuipch.h"
#include "ControlParent.h"

#include "core/reflection/Property.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ControlParent::GET_TYPE() {
        using namespace Ghurund::Core;

        static auto PROPERTY_FOCUS = Property<ControlParent, Control*>("Focus", &getFocus, &setFocus);

        static const Ghurund::Core::Type TYPE = TypeBuilder<ControlParent>(Ghurund::UI::NAMESPACE_NAME, "ControlParent")
            .withProperty(PROPERTY_FOCUS)
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
