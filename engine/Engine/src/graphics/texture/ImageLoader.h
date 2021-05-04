#pragma once

#include "Image.h"
#include "core/resource/Loader.h"

namespace Ghurund {
    class ImageLoader:public Loader {
    private:
        IWICImagingFactory* imageFactory;

        DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID) const;

        WICPixelFormatGUID getWICFormatFromDXGIFormat(DXGI_FORMAT format, bool* sRGB) const;

        WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID) const;

        int getDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat) const;

    public:
        ImageLoader(IWICImagingFactory* imageFactory):imageFactory(imageFactory) {}

        virtual Status load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, LoadOption options) const override;

        virtual Status save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, SaveOption options) const override;
    };
}