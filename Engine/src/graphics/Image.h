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
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead);

        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const {
            return Status::NOT_IMPLEMENTED;
        }

        virtual void clean() {
            delete[] imageData;
        }

    public:
        ~Image() {
            clean();
        }

        BYTE *getData() {
            return imageData;
        }

        DXGI_FORMAT getFormat() {
            return dxgiFormat;
        }

        unsigned int getWidth() {
            return width;
        }

        unsigned int getHeight() {
            return height;
        }

        unsigned int getPixelSize() {
            return pixelSize;
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