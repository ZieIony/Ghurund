#include "ghuipch.h"
#include "Style.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Style>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "Style", sizeof(Ghurund::UI::Style));
        return TYPE;
    }
}