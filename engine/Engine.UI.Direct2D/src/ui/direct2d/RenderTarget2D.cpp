#include "ghuidxpch.h"
#include "RenderTarget2D.h"

#include "Graphics2D.h"

namespace Ghurund::UI::Direct2D {
    Status RenderTarget2D::init(Graphics2D& graphics2d, ID3D12Resource& texture) {
        D3D11_RESOURCE_FLAGS d3d11Flags = { D3D11_BIND_RENDER_TARGET };
        if (FAILED(graphics2d.Device11->CreateWrappedResource(&texture, &d3d11Flags, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_RENDER_TARGET, IID_PPV_ARGS(&wrappedRenderTarget))))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateWrappedResource failed\n"));

        ComPtr<IDXGISurface> surface;
        if (FAILED(wrappedRenderTarget.As(&surface)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("m_wrappedRenderTarget.As(&surface) failed\n"));

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
        if (FAILED(graphics2d.DeviceContext.CreateBitmapFromDxgiSurface(surface.Get(), &bitmapProperties, d2dRenderTarget.GetAddressOf())))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateBitmapFromDxgiSurface failed\n"));

        return Status::OK;
    }
}
