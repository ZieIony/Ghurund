#pragma once

#include "Image.h"
#include "core/resource/Loader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ImageLoader:public Ghurund::Core::Loader {
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

        virtual Status load(
            Ghurund::Core::ResourceManager& manager,
            Ghurund::Core::MemoryInputStream& stream,
            Ghurund::Core::Resource& resource,
            const Ghurund::Core::ResourceFormat* format = nullptr,
            Ghurund::Core::LoadOption options = Ghurund::Core::LoadOption::DEFAULT
        ) override;

        virtual Status save(
            Ghurund::Core::ResourceManager& manager,
            Ghurund::Core::MemoryOutputStream& stream,
            Ghurund::Core::Resource& resource,
            const Ghurund::Core::ResourceFormat* format = nullptr,
            Ghurund::Core::SaveOption options = Ghurund::Core::SaveOption::DEFAULT
        ) const override;
    };
}