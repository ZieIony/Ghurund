#include "ghuipch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::IUIContext>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::IUIContext>();
        return TYPE;
    }
}