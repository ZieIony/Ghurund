#include "ghcpch.h"
#include "Image.h"

#include "ImageLoader.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    void Image::init(const Buffer& data, const IntSize& size, DXGI_FORMAT format) {
        imageData = data;
        this->size = size;
        this->format = format;
        this->pixelSize = ImageLoader::getDXGIFormatBitsPerPixel(format) / 8;
        rowPitch = ((uint32_t)(data.Size / size.Height));
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
        static auto PROPERTY_SIZE = Property<Image, const IntSize&>("Size", &getSize);
        static auto PROPERTY_PIXELSIZE = Property<Image, uint32_t>("PixelSize", &getPixelSize);
        static auto PROPERTY_ROWPITCH = Property<Image, uint32_t>("RowPitch", &getRowPitch);

        static const auto CONSTRUCTOR = Constructor<Image>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Image>()
            .withProperty(PROPERTY_DATA)
            .withProperty(PROPERTY_FORMAT)
            .withProperty(PROPERTY_SIZE)
            .withProperty(PROPERTY_PIXELSIZE)
            .withProperty(PROPERTY_ROWPITCH)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}