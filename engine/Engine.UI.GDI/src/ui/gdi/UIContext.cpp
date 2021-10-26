#include "ghuigdipch.h"
#include "UIContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::GDI::UIContext>() {
        static Type TYPE = Type(Ghurund::UI::GDI::NAMESPACE_NAME, "DirectXUIContext", sizeof(Ghurund::UI::GDI::UIContext));
        return TYPE;
    }
}