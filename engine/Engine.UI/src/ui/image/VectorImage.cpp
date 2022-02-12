#include "ghuipch.h"
#include "VectorImage.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"
#include "core/reflection/ReadOnlyProperty.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& VectorImage::GET_TYPE() {
        static auto PROPERTY_SIZE = ReadOnlyProperty<VectorImage, FloatSize>("Size", &getSize);

        static const auto CONSTRUCTOR = Constructor<VectorImage>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<VectorImage>(Ghurund::UI::NAMESPACE_NAME, "VectorImage")
            .withProperty(PROPERTY_SIZE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
