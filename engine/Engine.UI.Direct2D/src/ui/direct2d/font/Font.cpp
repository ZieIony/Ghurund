#include "ghuidxpch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/ReadOnlyProperty.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<IDWriteFontCollection>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "IDWriteFontCollection", sizeof(IDWriteFontCollection*));
        return TYPE;
    }
}

namespace Ghurund::UI::Direct2D
{
    const Ghurund::Core::Type& Font::GET_TYPE() {
        static auto PROPERTY_COLLECTION = ReadOnlyProperty<Font, IDWriteFontCollection*>("Collection", &getCollection);

        static const auto CONSTRUCTOR = Constructor<Font>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Font>(Ghurund::UI::Direct2D::NAMESPACE_NAME, "Font")
            .withProperty(PROPERTY_COLLECTION)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}