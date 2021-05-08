#pragma once

#include "Image.h"
#include "core/resource/Loader.h"

namespace Ghurund::UI {
    class ImageLoader:public Loader {
    private:
        IWICImagingFactory* imageFactory;

        DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID) const;

        WICPixelFormatGUID getWICFormatFromDXGIFormat(DXGI_FORMAT format, bool* sRGB) const;

        WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID) const;

        int getDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat) const;

    public:
        ~ImageLoader() {
            if (imageFactory)
                imageFactory->Release();
        }

        Status init() {
            HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory));
            if (FAILED(hr))
                return Status::CALL_FAIL;
            return Status::OK;
        }

        virtual Status load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, LoadOption options) override;

        virtual Status save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, SaveOption options) const override;
    };
}