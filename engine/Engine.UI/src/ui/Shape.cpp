#include "ghuipch.h"
#include "Shape.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Shape>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "Shape", sizeof(Ghurund::UI::Shape));
        return TYPE;
    }
}
