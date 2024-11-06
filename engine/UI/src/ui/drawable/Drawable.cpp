#include "ghuipch.h"
#include "Drawable.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Drawable::GET_TYPE() {
        static auto PROPERTY_PREFERREDSIZE = Property<Drawable, const FloatSize&>("PreferredSize", &getPreferredSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<Drawable>()
            .withProperty(PROPERTY_PREFERREDSIZE)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}