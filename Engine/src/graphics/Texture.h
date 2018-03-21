#pragma once

#include "Graphics.h"
#include "Fence.h"
#include "core/Logger.h"
#include "Image.h"

namespace Ghurund {
    class Texture {
    private:
        ComPtr<ID3D12Resource> textureResource;
        ComPtr<ID3D12Resource> textureUploadHeap;

    public:
        ComPtr<ID3D12DescriptorHeap> srvHeap;

        Status init(Graphics &graphics, ComPtr<ID3D12GraphicsCommandList> commandList, Image *image);
 
    };
}