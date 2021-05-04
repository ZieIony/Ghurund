#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "core/resource/ResourceManager.h"

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

#include <wincodec.h>

namespace Ghurund {
    using namespace DirectX;

    class Image: public Resource {
    private:
        DXGI_FORMAT format;
        uint32_t width, height, pixelSize, rowPitch;
        Buffer imageData;

    protected:
        static const Ghurund::Type& GET_TYPE();

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

        __declspec(property(get = getData)) Buffer& Data;

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = { (ResourceFormat*)&ResourceFormat::JPG, (ResourceFormat*)&ResourceFormat::JPEG, (ResourceFormat*)&ResourceFormat::PNG };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
    };
}