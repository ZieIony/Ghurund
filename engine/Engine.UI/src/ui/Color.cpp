#include "ghuipch.h"
#include "Color.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Color>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "Color", sizeof(Ghurund::UI::Color));
        return TYPE;
    }
}
