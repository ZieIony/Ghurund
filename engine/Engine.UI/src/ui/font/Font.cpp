#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Font::GET_TYPE() {
        static auto PROPERTY_FAMILYNAME = Property<Font, const WString&>("FamilyName", &getFamilyName);

        static const auto CONSTRUCTOR = Constructor<Font>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Font>(Ghurund::UI::NAMESPACE_NAME, "Font")
            .withProperty(PROPERTY_FAMILYNAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}