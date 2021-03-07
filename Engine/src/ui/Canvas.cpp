#include "ghpch.h"
#include "Canvas.h"

#include "graphics/SwapChain.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/drawable/SvgImage.h"

namespace Ghurund::UI {
    Status Canvas::init(Graphics2D& graphics2d) {
        this->deviceContext = graphics2d.DeviceContext;
        this->graphics2d = &graphics2d;

        deviceContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        if (FAILED(deviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &fillBrush)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateSolidColorBrush failed\n");

        if(FAILED(deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &tintEffect)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateEffect failed\n");

        deviceContext->CreateEffect(CLSID_D2D1Shadow, &shadowEffect);

        deviceContext->CreateEffect(CLSID_D2D1Flood, &floodEffect);
        floodEffect->SetValue(D2D1_FLOOD_PROP_COLOR, D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f));

        return Status::OK;
    }

    void Canvas::endPaint() {
        if (matrixStack.Size != 1)
            Logger::log(LogType::INFO, _T("mismatched calls to Canvas::save() and Canvas::restore()\n"));
        matrixStack.clear();
    }
    
    void Canvas::drawImage(BitmapImage& image, const FloatRect& dst, float alpha) {
        D2D1_RECT_F d = { dst.left, dst.top, dst.right, dst.bottom };
        deviceContext->DrawBitmap(image.Data, d, alpha);
    }
    
    void Canvas::drawImage(BitmapImage& image, const FloatRect& dst, const Color& color, float alpha) {
        tintEffect->SetInput(0, image.Data);
        D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, color.A * alpha, color.R, color.G, color.B, 0);
        tintEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
        deviceContext->DrawImage(tintEffect.Get(), D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
    }
    
    void Canvas::drawImage(BitmapImage& image, const FloatRect& src, const FloatRect& dst, float alpha) {
        D2D1_RECT_F s = { src.left, src.top, src.right, src.bottom };
        D2D1_RECT_F d = { dst.left, dst.top, dst.right, dst.bottom };
        deviceContext->DrawBitmap(image.Data, d, alpha, D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC, s);
    }
    
    void Canvas::drawImage(BitmapImage& image, const FloatRect& src, const FloatRect& dst, const Color& color, float alpha) {
        tintEffect->SetInput(0, image.Data);
        D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, color.A * alpha, color.R, color.G, color.B, 0);
        tintEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
        deviceContext->DrawImage(tintEffect.Get(), D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
    }
    
    void Canvas::drawImage(SvgImage& image) {
        deviceContext->DrawSvgDocument(image.Data);
    }
    
    void Canvas::drawShadow(BitmapImage& image, float radius, const Color& color) {
        shadowEffect->SetInput(0, image.Data);
        shadowEffect->SetValue(D2D1_SHADOW_PROP_COLOR, color.Vector);
        shadowEffect->SetValue(D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION, radius);
        deviceContext->DrawImage(shadowEffect.Get(), D2D1_INTERPOLATION_MODE_LINEAR);
    }
}
