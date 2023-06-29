#pragma once

#include "Image.h"
#include "core/resource/Loader.h"
#include "core/Exceptions.h"

namespace Ghurund::Core {
    class ImageLoader:public Loader {
    private:
        IWICImagingFactory* imageFactory = nullptr;

    public:
        static DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID);

        static WICPixelFormatGUID getWICFormatFromDXGIFormat(DXGI_FORMAT format, bool* sRGB);

        static WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID);

        static int getDXGIFormatBitsPerPixel(DXGI_FORMAT dxgiFormat);

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
            const ResourceManager& manager,
            MemoryOutputStream& stream,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override;
    };
}