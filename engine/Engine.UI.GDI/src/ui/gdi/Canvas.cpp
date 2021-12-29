#include "ghuigdipch.h"
#include "Canvas.h"

#include "ui/gdi/Shape.h"

namespace Ghurund::UI::GDI {
    Status Canvas::init(HWND hwnd) {
        this->hwnd = hwnd;
        BufferedPaintInit();
        pen = new Gdiplus::Pen(Gdiplus::Color());
        brush = new Gdiplus::SolidBrush(Gdiplus::Color());
        colorMatrixEffect = new Gdiplus::ColorMatrixEffect();
        colorMatrix = {
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        matrix = new Gdiplus::Matrix();

        return Status::OK;
    }

    void Canvas::uninit() {
        BufferedPaintUnInit();
        delete matrix;
        delete colorMatrixEffect;
        delete pen;
        delete brush;
    }

    void Canvas::beginPaint() {
        if (bitmap) {
            graphics = Gdiplus::Graphics::FromImage(bitmap);
        } else {
            hdc = GetDC(hwnd);// BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            HDC memdc;
            hbuff = BeginBufferedPaint(hdc, &rc, BPBF_COMPATIBLEBITMAP, NULL, &memdc);
            graphics = Gdiplus::Graphics::FromHDC(memdc);
        }
        graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
        graphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
    }

    void Canvas::endPaint() {
        if (!bitmap) {
            EndBufferedPaint(hbuff, TRUE);
            ReleaseDC(hwnd, hdc);
            //EndPaint(hwnd, &ps);
        }
        delete graphics;
        graphics = nullptr;
    }

    void Canvas::drawRect(float x, float y, float width, float height, const Color& color, float thickness, IStrokeStyle* strokeStyle) {
        this->color.SetValue(color);
        if (strokeStyle)
            pen->SetDashStyle(((StrokeStyle*)strokeStyle)->get());
        pen->SetWidth(thickness);
        pen->SetColor(this->color);
        graphics->DrawRectangle(pen, Gdiplus::RectF(x - 0.5f, y - 0.5f, width, height));
    }

    void Canvas::fillRect(float x, float y, float width, float height, const Color& color) {
        this->color.SetValue(color);
        brush->SetColor(this->color);
        graphics->FillRectangle(brush, Gdiplus::RectF(x - 0.5f, y - 0.5f, width, height));
    }

    void Canvas::drawShape(Ghurund::UI::Shape& shape, const Color& color, float thickness) {
        this->color.SetValue(color);
        pen->SetWidth(thickness);
        pen->SetColor(this->color);
        graphics->DrawPath(pen, ((Ghurund::UI::GDI::Shape&)shape).Path);
    }

    void Canvas::drawLine(float x1, float y1, float x2, float y2, const Color& color, float thickness, IStrokeStyle* strokeStyle) {
        this->color.SetValue(color);
        if (strokeStyle)
            pen->SetDashStyle(((StrokeStyle*)strokeStyle)->get());
        pen->SetWidth(thickness);
        pen->SetColor(this->color);
        path.Reset();
        path.AddLine(Gdiplus::PointF(x1 - 0.5f, y1 - 0.5f), Gdiplus::PointF(x2 - 0.5f, y2 - 0.5f));
        graphics->DrawPath(pen, &path);
    }
    
    void Canvas::drawImage(Bitmap& bitmapImage, const FloatRect& dst, float alpha) {
        //D2D1_RECT_F d = { dst.left, dst.top, dst.right, dst.bottom };
        //deviceContext->DrawBitmap(bitmapImage, d, alpha);
    }
    
    void Canvas::drawImage(Bitmap& bitmapImage, const FloatRect& dst, const Color& color, float alpha) {
        /*tintEffect->SetInput(0, bitmapImage);
        D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, color.A * alpha, color.R, color.G, color.B, 0);
        tintEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
        deviceContext->DrawImage(tintEffect.Get(), D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);*/
    }
    
    void Canvas::drawImage(Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, float alpha) {
        /*D2D1_RECT_F s = {src.left, src.top, src.right, src.bottom};
        D2D1_RECT_F d = { dst.left, dst.top, dst.right, dst.bottom };
        deviceContext->DrawBitmap(bitmapImage, d, alpha, D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC, s);*/
    }
    
    void Canvas::drawImage(Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, const Color& color, float alpha) {
        /*tintEffect->SetInput(0, bitmapImage);
        D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, color.A * alpha, color.R, color.G, color.B, 0);
        tintEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
        deviceContext->DrawImage(tintEffect.Get(), D2D1_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC);*/
    }
    
    void Canvas::drawImage(VectorImage& svgDocument) {
        //deviceContext->DrawSvgDocument(&svgDocument);
    }
    
    /*void Canvas::drawShadow(ID2D1Bitmap1* bitmapImage, float radius, const Color& color) {
        /*shadowEffect->SetInput(0, bitmapImage);
        shadowEffect->SetValue(D2D1_SHADOW_PROP_COLOR, D2D_VECTOR_4F(color.R, color.G, color.B, color.A));
        shadowEffect->SetValue(D2D1_SHADOW_PROP_BLUR_STANDARD_DEVIATION, radius);
        deviceContext->DrawImage(shadowEffect.Get(), D2D1_INTERPOLATION_MODE_LINEAR);* /
    }*/
}
