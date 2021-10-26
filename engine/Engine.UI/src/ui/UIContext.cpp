#include "ghuipch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::IUIContext>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "IUIContext", sizeof(Ghurund::UI::IUIContext));
        return TYPE;
    }
}