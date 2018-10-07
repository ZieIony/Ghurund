#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "Ghurund.h"
#include "resource/ResourceManager.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include <wrl.h>
#include <wincodec.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class Image: public Resource {
    private:
        DXGI_FORMAT dxgiFormat;
        unsigned int width, height, pixelSize;
        BYTE *imageData = nullptr;

        DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID);

        WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID);

        int getDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat);

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options);

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const {
            return Status::NOT_IMPLEMENTED;
        }

    public:
        ~Image() {
            delete[] imageData;
        }

        BYTE *getData() {
            return imageData;
        }

        __declspec(property(get = getData)) BYTE *Data;

        DXGI_FORMAT getFormat() {
            return dxgiFormat;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        unsigned int getWidth() {
            return width;
        }

        __declspec(property(get = getWidth)) unsigned int Width;

        unsigned int getHeight() {
            return height;
        }

        __declspec(property(get = getHeight)) unsigned int Height;

        unsigned int getPixelSize() {
            return pixelSize;
        }

        __declspec(property(get = getPixelSize)) unsigned int PixelSize;

        virtual const Ghurund::Type &getType() const override {
            return Type::IMAGE;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::JPG};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::JPG;
        }
    };
}