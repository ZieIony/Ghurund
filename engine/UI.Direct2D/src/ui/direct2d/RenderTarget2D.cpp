#include "ghuid2dpch.h"
#include "RenderTarget2D.h"

#include "Graphics2D.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI::Direct2D {
    void RenderTarget2D::init(NotNull<Graphics2D> graphics2d, NotNull<ID3D12Resource> texture) {
        D3D11_RESOURCE_FLAGS d3d11Flags = { D3D11_BIND_RENDER_TARGET };
        if (FAILED(graphics2d->Device11->CreateWrappedResource(
            &texture, &d3d11Flags, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_RENDER_TARGET, IID_PPV_ARGS(&wrappedRenderTarget))
            )) {
            Logger::log(LogType::ERR0R, _T("CreateWrappedResource failed\n"));
            throw CallFailedException();
        }

        ComPtr<IDXGISurface> surface;
        if (FAILED(wrappedRenderTarget.As(&surface))) {
            Logger::log(LogType::ERR0R, _T("m_wrappedRenderTarget.As(&surface) failed\n"));
            throw CallFailedException();
        }

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
        if (FAILED(graphics2d->DeviceContext->CreateBitmapFromDxgiSurface(surface.Get(), &bitmapProperties, d2dRenderTarget.GetAddressOf()))) {
            Logger::log(LogType::ERR0R, _T("CreateBitmapFromDxgiSurface failed\n"));
            throw CallFailedException();
        }
    }
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::RenderTarget2D>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::Direct2D::RenderTarget2D>();
        return TYPE;
    }
}