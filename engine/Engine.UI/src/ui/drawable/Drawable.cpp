#include "ghuipch.h"
#include "Drawable.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Drawable::GET_TYPE() {
        static auto PROPERTY_PREFERREDSIZE = Property<Drawable, const FloatSize&>("PreferredSize", &getPreferredSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<Drawable>(Ghurund::UI::NAMESPACE_NAME, "Drawable")
            .withProperty(PROPERTY_PREFERREDSIZE)
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}