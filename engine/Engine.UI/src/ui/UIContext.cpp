#include "ghuipch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::UIContext>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "UIContext", sizeof(Ghurund::UI::UIContext));
        return TYPE;
    }
}