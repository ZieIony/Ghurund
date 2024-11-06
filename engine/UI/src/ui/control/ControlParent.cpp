#include "ghuipch.h"
#include "ControlParent.h"

#include "core/reflection/Property.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ControlParent::GET_TYPE() {
        using namespace Ghurund::Core;

        static auto PROPERTY_FOCUS = Property<ControlParent, Control*>("Focus", &getFocus, &setFocus);

        static const Ghurund::Core::Type TYPE = TypeBuilder<ControlParent>()
            .withProperty(PROPERTY_FOCUS)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
