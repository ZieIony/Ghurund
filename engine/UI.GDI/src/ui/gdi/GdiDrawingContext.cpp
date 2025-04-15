#include "ghuigdipch.h"
#include "GdiDrawingContext.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::GDI::GdiDrawingContext>() {
        static const Type TYPE = TypeBuilder<Ghurund::UI::GDI::GdiDrawingContext>();
        return TYPE;
    }
}