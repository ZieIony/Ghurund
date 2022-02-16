#include "ghuipch.h"
#include "Bitmap.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Bitmap::GET_TYPE() {
        static auto PROPERTY_SIZE = Property<Bitmap, IntSize>("Size", &getSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<Bitmap>(Ghurund::UI::NAMESPACE_NAME, "Bitmap")
            .withProperty(PROPERTY_SIZE)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}