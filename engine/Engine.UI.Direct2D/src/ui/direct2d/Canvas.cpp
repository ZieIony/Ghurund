#include "ghuidxpch.h"
#include "Canvas.h"

#include "ui/direct2d/image/Bitmap.h"
#include <ui/direct2d/image/SvgDocument.h>

namespace Ghurund::UI::Direct2D {
    Status Canvas::init(ID2D1DeviceContext5& deviceContext) {
        using namespace Ghurund::Core;
        this->deviceContext = &deviceContext;

        deviceContext.SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        if (FAILED(deviceContext.CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &fillBrush)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateSolidColorBrush failed\n"));

        if (FAILED(deviceContext.CreateEffect(CLSID_D2D1ColorMatrix, &tintEffect)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("CreateEffect failed\n"));

        return Status::OK;
    }

    void Canvas::uninit() {
        fillBrush.Reset();
        strokeBrush.Reset();
        matrixStack.clear();
        deviceContext = nullptr;
        tintEffect.Reset();
    }

    void Canvas::endPaint() {
        using namespace Ghurund::Core;
        if (matrixStack.Size != 1)
            Logger::log(LogType::INFO, _T("mismatched calls to Canvas::save() and Canvas::restore()\n"));
        matrixStack.clear();
    }

    void Canvas::drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, float alpha) {
#ifdef _DEBUG
        if (alpha == 0.0f || dst.Width == 0.0f || dst.Height == 0.0f) {
            Logger::log(LogType::WARNING, _T("A draw call that doesn't draw anything.\n"));
            return;
        }
#endif
        D2D1_RECT_F d = { dst.left, dst.top, dst.right, dst.bottom };
        deviceContext->DrawBitmap(((Ghurund::UI::Direct2D::Bitmap&)bitmapImage).Data, d, alpha);
    }

    void Canvas::drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, const Color& color, float alpha) {
#ifdef _DEBUG
        if (color.A == 0.0f || alpha == 0.0f || dst.Width == 0.0f || dst.Height == 0.0f) {
            Logger::log(LogType::WARNING, _T("A draw call that doesn't draw anything.\n"));
            return;
        }
#endif
        tintEffect->SetInput(0, ((Ghurund::UI::Direct2D::Bitmap&)bitmapImage).Data);
        D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, color.A * alpha, color.R, color.G, color.B, 0);
        tintEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
        deviceContext->DrawImage(tintEffect.Get(), D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
    }

    void Canvas::drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, float alpha) {
#ifdef _DEBUG
        if (alpha == 0.0f || dst.Width == 0.0f || dst.Height == 0.0f) {
            Logger::log(LogType::WARNING, _T("A draw call that doesn't draw anything.\n"));
            return;
        }
#endif
        D2D1_RECT_F s = { src.left, src.top, src.right, src.bottom };
        D2D1_RECT_F d = { dst.left, dst.top, dst.right, dst.bottom };
        deviceContext->DrawBitmap(((Ghurund::UI::Direct2D::Bitmap&)bitmapImage).Data, d, alpha, D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC, s);
    }

    void Canvas::drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, const Color& color, float alpha) {
#ifdef _DEBUG
        if (color.A == 0.0f || alpha == 0.0f || dst.Width == 0.0f || dst.Height == 0.0f) {
            Logger::log(LogType::WARNING, _T("A draw call that doesn't draw anything.\n"));
            return;
        }
#endif
        tintEffect->SetInput(0, ((Ghurund::UI::Direct2D::Bitmap&)bitmapImage).Data);
        D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, color.A * alpha, color.R, color.G, color.B, 0);
        tintEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
        deviceContext->DrawImage(tintEffect.Get(), D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);
    }

    void Canvas::drawImage(VectorImage& svgDocument) {
        deviceContext->DrawSvgDocument(((SvgDocument&)svgDocument).Data);
    }

    /*void Canvas::drawShadow(ID2D1Bitmap1* bitmapImage, float radius, const Color& color) {
        /*shadowEffect->SetInput(0, bitmapImage);
        shadowEffect->SetValue(D2D1_SHADOW_PROP_COLOR, D2D_VECTOR_4F(color.R, color.G, color.B, color.A));
        shadowEffect->SetValue(D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION, radius);
        deviceContext->DrawImage(shadowEffect.Get(), D2D1_INTERPOLATION_MODE_LINEAR);* /
    }*/
}
