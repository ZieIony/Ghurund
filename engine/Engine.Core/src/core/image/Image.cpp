#include "ghcpch.h"
#include "Image.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<DXGI_FORMAT>() {
        static Type TYPE = Type("", "DXGI_FORMAT", sizeof(DXGI_FORMAT));
        return TYPE;
    }

    const Ghurund::Core::Type& Image::GET_TYPE() {
        using namespace Ghurund::Core;

        static auto PROPERTY_DATA = ReadOnlyProperty<Image, Buffer&>("Data", &getData);
        static auto PROPERTY_FORMAT = ReadOnlyProperty<Image, DXGI_FORMAT>("Format", &getFormat);
        static auto PROPERTY_WIDTH = ReadOnlyProperty<Image, uint32_t>("Width", &getWidth);
        static auto PROPERTY_HEIGHT = ReadOnlyProperty<Image, uint32_t>("Height", &getHeight);
        static auto PROPERTY_PIXELSIZE = ReadOnlyProperty<Image, uint32_t>("PixelSize", &getPixelSize);
        static auto PROPERTY_ROWPITCH = ReadOnlyProperty<Image, uint32_t>("RowPitch", &getRowPitch);

        static const auto CONSTRUCTOR = Constructor<Image>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Image>(Ghurund::Core::NAMESPACE_NAME, "Image")
            .withProperty(PROPERTY_DATA)
            .withProperty(PROPERTY_FORMAT)
            .withProperty(PROPERTY_WIDTH)
            .withProperty(PROPERTY_HEIGHT)
            .withProperty(PROPERTY_PIXELSIZE)
            .withProperty(PROPERTY_ROWPITCH)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}