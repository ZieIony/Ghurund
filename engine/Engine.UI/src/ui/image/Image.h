#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "core/resource/ResourceManager.h"

#pragma warning(push, 0)
#include <dxgi1_4.h>
#pragma warning(pop)

#include <wincodec.h>

#include "reflection_7103238f_73b0_463d_bc7f_54055f691499.h"

namespace Ghurund::UI {

    class Image: public Resource {
        reflection_7103238f_73b0_463d_bc7f_54055f691499

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

        static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", true, true);
        static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", true, true);
        static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", true, true);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };

        virtual const Array<ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}