#pragma once

#include "Image.h"
#include "core/resource/Loader.h"
#include "core/exception/Exceptions.h"

namespace Ghurund::Core {
    class ImageLoader:public Loader {
    private:
        IWICImagingFactory* imageFactory = nullptr;

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        static DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID);

        static WICPixelFormatGUID getWICFormatFromDXGIFormat(DXGI_FORMAT format, bool* sRGB);

        static WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID);

        static int getDXGIFormatBitsPerPixel(DXGI_FORMAT dxgiFormat);

        ImageLoader() {
            HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imageFactory));
            if (FAILED(hr))
                throw CallFailedException();
        }

        ~ImageLoader() {
            if (imageFactory)
                imageFactory->Release();
        }
    };
}