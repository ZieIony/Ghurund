#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "core/resource/ResourceManager.h"

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

#include <wincodec.h>

#include "reflection_4db8630b_3fe3_4f0c_b730_e1ec12b0e449.h"

namespace Ghurund::UI {

    class Image: public Resource {
        reflection_4db8630b_3fe3_4f0c_b730_e1ec12b0e449

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

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"jpg", true, true),
                ResourceFormat(L"jpeg", true, true),
                ResourceFormat(L"png", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}