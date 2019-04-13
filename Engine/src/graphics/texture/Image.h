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
        DXGI_FORMAT format;
        UINT32 width, height, pixelSize, rowPitch;
        Buffer* imageData = nullptr;

        DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID) const;

        WICPixelFormatGUID getWICFormatFromDXGIFormat(DXGI_FORMAT format, bool* sRGB = nullptr) const;

        WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID) const;

        int getDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat);

    protected:
        virtual Status loadInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

    public:
        Image() {}

        Image(Buffer& data, UINT32 width, UINT32 height, DXGI_FORMAT format):
            imageData(ghnew Buffer(data)),
            width(width),
            height(height),
            format(format),
            pixelSize(getDXGIFormatBitsPerPixel(format) / 8),
            rowPitch(data.Size / height) {

            Valid = true;
        }

        ~Image() {
            delete imageData;
        }

        Buffer& getData() {
            return *imageData;
        }

        __declspec(property(get = getData)) Buffer& Data;

        DXGI_FORMAT getFormat() {
            return format;
        }

        __declspec(property(get = getFormat)) DXGI_FORMAT Format;

        UINT32 getWidth() {
            return width;
        }

        __declspec(property(get = getWidth)) UINT32 Width;

        UINT32 getHeight() {
            return height;
        }

        __declspec(property(get = getHeight)) UINT32 Height;

        UINT32 getPixelSize() {
            return pixelSize;
        }

        __declspec(property(get = getPixelSize)) UINT32 PixelSize;

        UINT32 getRowPitch() {
            return rowPitch;
        }

        __declspec(property(get = getRowPitch)) UINT32 RowPitch;

        virtual const Ghurund::Type& getType() const override {
            return Type::IMAGE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::JPG, (ResourceFormat*)& ResourceFormat::JPEG, (ResourceFormat*)& ResourceFormat::PNG};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;

        Status SaveWICTextureToFile(ResourceManager& resourceManager,
            ResourceContext& context,
            ID3D12Resource* pSource,
            const wchar_t* fileName,
            D3D12_RESOURCE_STATES beforeState,
            D3D12_RESOURCE_STATES afterState);
    };
}