#include "ghuipch.h"
#include "ImageScaleMode.h"

#include "core/reflection/Type.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::ImageScaleMode>() {
        static Type TYPE = Type("ImageScaleMode", sizeof(Ghurund::UI::ImageScaleMode));
        return TYPE;
    }
}
