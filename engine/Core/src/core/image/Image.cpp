#include "ghcpch.h"
#include "Image.h"

#include "ImageLoader.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    void Image::init(const Buffer& data, uint32_t width, uint32_t height, DXGI_FORMAT format) {
        imageData = data;
        this->width = width;
        this->height = height;
        this->format = format;
        this->pixelSize = ImageLoader::getDXGIFormatBitsPerPixel(format) / 8;
        rowPitch = ((uint32_t)(data.Size / height));

        Valid = true;
    }

    template<>
    const Type& getType<DXGI_FORMAT>() {
        static Type TYPE = Type("", "DXGI_FORMAT", sizeof(DXGI_FORMAT));
        return TYPE;
    }

    const Ghurund::Core::Type& Image::GET_TYPE() {
        using namespace Ghurund::Core;

        static auto PROPERTY_DATA = Property<Image, Buffer&>("Data", &getData);
        static auto PROPERTY_FORMAT = Property<Image, DXGI_FORMAT>("Format", &getFormat);
        static auto PROPERTY_WIDTH = Property<Image, uint32_t>("Width", &getWidth);
        static auto PROPERTY_HEIGHT = Property<Image, uint32_t>("Height", &getHeight);
        static auto PROPERTY_PIXELSIZE = Property<Image, uint32_t>("PixelSize", &getPixelSize);
        static auto PROPERTY_ROWPITCH = Property<Image, uint32_t>("RowPitch", &getRowPitch);

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