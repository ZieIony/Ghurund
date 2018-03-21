#pragma once

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
    class Image {
    private:
        DXGI_FORMAT dxgiFormat;
        unsigned int width, height, pixelSize;
        BYTE *imageData = nullptr;

        DXGI_FORMAT getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID);

        WICPixelFormatGUID convertToWICFormat(WICPixelFormatGUID& wicFormatGUID);

        int getDXGIFormatBitsPerPixel(DXGI_FORMAT& dxgiFormat);

    public:
        ~Image() {
            delete[] imageData;
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

        Status loadImageDataFromFile(ResourceManager &resourceManager, LPCWSTR filename);
    };
}