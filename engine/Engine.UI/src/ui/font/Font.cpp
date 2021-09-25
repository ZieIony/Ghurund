#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<IDWriteFontCollection>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "IDWriteFontCollection", sizeof(IDWriteFontCollection*));
        return TYPE;
    }
}

namespace Ghurund::UI {
    const Ghurund::Core::Type& Font::GET_TYPE() {
        static auto PROPERTY_FAMILYNAME = ReadOnlyProperty<Font, const WString&>("FamilyName", &getFamilyName);
        static auto PROPERTY_COLLECTION = ReadOnlyProperty<Font, IDWriteFontCollection*>("Collection", &getCollection);

        static const auto CONSTRUCTOR = Constructor<Font>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Font>(Ghurund::UI::NAMESPACE_NAME, "Font")
            .withProperty(PROPERTY_FAMILYNAME)
            .withProperty(PROPERTY_COLLECTION)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}