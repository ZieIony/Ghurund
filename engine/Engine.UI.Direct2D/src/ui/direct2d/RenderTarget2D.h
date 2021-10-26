#pragma once

#include "core/logging/Logger.h"

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <d3d11on12.h>
#include <wrl.h>

namespace Ghurund::UI::Direct2D {
    using namespace Microsoft::WRL;
    using namespace Ghurund::Core;

    class Graphics2D;

    class RenderTarget2D {
    private:
        ComPtr<ID3D11Resource> wrappedRenderTarget;
        ComPtr<ID2D1Bitmap1> d2dRenderTarget;

    public:
        inline ID3D11Resource* getWrappedTarget() const {
            return wrappedRenderTarget.Get();
        }

        __declspec(property(get = getWrappedTarget)) ID3D11Resource* WrappedTarget;

        inline ID2D1Bitmap1* getTarget2D() const {
            return d2dRenderTarget.Get();
        }

        __declspec(property(get = getTarget2D)) ID2D1Bitmap1* Target2D;

        Status init(Graphics2D& graphics2d, ID3D12Resource& texture);

        void uninit() {
            d2dRenderTarget.Reset();
            wrappedRenderTarget.Reset();
        }
    };

}