#include "ghuigdipch.h"
#include "SvgDrawable.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI::GDI {
    const Ghurund::Core::Type& SvgDrawable::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SvgDrawable>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
