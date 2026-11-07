#pragma once

#include "DxGraphics.h"

#include "core/Color.h"
#include "engine/directx/buffer/DepthBuffer.h"
#include "engine/directx/buffer/RenderTarget.h"
#include "rendering/DxGraphicsCommandList.h"

#include <d3d12.h>

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;

    class Frame {
    private:
        DxGraphicsCommandList* startCommandList;
        DxGraphicsCommandList* renderCommandList;
        D3D12_VIEWPORT viewport = {};
        D3D12_RECT scissorRect = {};
        RenderTarget* renderTarget = nullptr;
        DepthBuffer* depthBuffer = nullptr;

    public:
        Frame() {
            startCommandList = ghnew DxGraphicsCommandList();
            renderCommandList = ghnew DxGraphicsCommandList();
        }

        ~Frame() {
            startCommandList->release();
            renderCommandList->release();
            delete renderTarget;
            delete depthBuffer;
        }

        void init(DxGraphics& graphics, D3D12_VIEWPORT& viewport, D3D12_RECT& scissorRect, RenderTarget* renderTarget, DepthBuffer* depthBuffer);

        void start();
        void startFrame(CommandList& commandList);
        void clear(const Color* color);
        void finish();
        void flush();

        inline RenderTarget& getRenderTarget() {
            return *renderTarget;
        }

        __declspec(property(get = getRenderTarget)) RenderTarget& RenderTarget;

        inline DxGraphicsCommandList* getStartCommandList() const {
            return startCommandList;
        }

        __declspec(property(get = getStartCommandList)) DxGraphicsCommandList* StartCommandList;

        inline DxGraphicsCommandList* getRenderCommandList() const {
            return renderCommandList;
        }

        __declspec(property(get = getRenderCommandList)) DxGraphicsCommandList* RenderCommandList;
    };
}
