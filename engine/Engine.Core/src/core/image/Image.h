#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "core/resource/ResourceManager.h"

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

#include <wincodec.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<DXGI_FORMAT>();

    class Image: public Resource {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        DXGI_FORMAT format;
        uint32_t width, height, pixelSize, rowPitch;
        Buffer imageData;

    public:
        void init(const Buffer& data, uint32_t width, uint32_t height, DXGI_FORMAT format, uint32_t pixelSize) {
            imageData = data;
            this->width = width;
            this->height = height;
            this->format = format;
            this->pixelSize = pixelSize;
            rowPitch = ((uint32_t)(data.Size / height));

            Valid = true;
        }

        Buffer& getData() {
            return imageData;
        }

        __declspec(property(get = getData)) Ghurund::Core::Buffer& Data;

        DXGI_FORMAT getFormat() {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        uint32_t getWidth() {
            return width;
        }

        __declspec(property(get = getWidth)) uint32_t Width;

        uint32_t getHeight() {
            return height;
        }

        __declspec(property(get = getHeight)) uint32_t Height;

        uint32_t getPixelSize() {
            return pixelSize;
        }

        __declspec(property(get = getPixelSize)) uint32_t PixelSize;

        uint32_t getRowPitch() {
            return rowPitch;
        }

        __declspec(property(get = getRowPitch)) uint32_t RowPitch;

        static const inline Ghurund::Core::ResourceFormat FORMAT_JPG = Ghurund::Core::ResourceFormat(L"jpg", true, true);
        static const inline Ghurund::Core::ResourceFormat FORMAT_JPEG = Ghurund::Core::ResourceFormat(L"jpeg", true, true);
        static const inline Ghurund::Core::ResourceFormat FORMAT_PNG = Ghurund::Core::ResourceFormat(L"png", true, true);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}