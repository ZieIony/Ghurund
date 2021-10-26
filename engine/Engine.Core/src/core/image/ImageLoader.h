#pragma once

#include "Image.h"
#include "core/resource/Loader.h"
#include "core/Exceptions.h"

namespace Ghurund::Core {
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

        void init() {
            HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory));
            if (FAILED(hr))
                throw CallFailedException();
        }

        virtual Image* load(
            ResourceManager& manager,
            MemoryInputStream& stream,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override;

        virtual void save(
            ResourceManager& manager,
            MemoryOutputStream& stream,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override;
    };
}