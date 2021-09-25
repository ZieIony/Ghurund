#include "ghuipch.h"
#include "Drawable.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Drawable::GET_TYPE() {
        static auto PROPERTY_SIZE = Property<Drawable, FloatSize&>("Size", (FloatSize & (Drawable::*)()) & getSize, (void(Drawable::*)(const FloatSize&)) & setSize);
        static auto PROPERTY_PREFERREDSIZE = ReadOnlyProperty<Drawable, const Ghurund::UI::PreferredSize&>("PreferredSize", (Ghurund::UI::PreferredSize & (Drawable::*)()) & getPreferredSize);
        static auto PROPERTY_OWNER = Property<Drawable, Control*>("Owner", (Control * (Drawable::*)()) & getOwner, (void(Drawable::*)(Control*)) & setOwner);

        static const Ghurund::Core::Type TYPE = TypeBuilder<Drawable>(Ghurund::UI::NAMESPACE_NAME, "Drawable")
            .withProperty(PROPERTY_SIZE)
            .withProperty(PROPERTY_PREFERREDSIZE)
            .withProperty(PROPERTY_OWNER)
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}