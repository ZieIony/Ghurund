#include "ghuipch.h"
#include "SizeConstraints.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::SizeConstraints>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "SizeConstraints", sizeof(Ghurund::UI::SizeConstraints));
        return TYPE;
    }
}