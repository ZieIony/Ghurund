#include "ghuipch.h"
#include "VectorImage.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& VectorImage::GET_TYPE() {
        static auto PROPERTY_SIZE = Property<VectorImage, FloatSize>("Size", &getSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<VectorImage>(Ghurund::UI::NAMESPACE_NAME, "VectorImage")
            .withProperty(PROPERTY_SIZE)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
