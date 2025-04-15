#include "ghuigdipch.h"
#include "UiContext.h"

#include <core/reflection/TypeBuilder.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::GDI::UiContext>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::GDI::UiContext>();
        return TYPE;
    }
}