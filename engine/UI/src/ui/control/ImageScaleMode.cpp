#include "ghuipch.h"
#include "ImageScaleMode.h"

#include "core/reflection/Type.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::ImageScaleMode>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ImageScaleMode>();
        return TYPE;
    }
}
