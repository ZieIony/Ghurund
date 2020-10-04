#include "GdiCanvas.h"
#include "GdiDrawingCache.h"

namespace Ghurund::UI {
    void GdiCanvas::drawImage(const GdiImage& image, float x, float y, float width, float height, int32_t tintColor) {
        matrix->Reset();
        matrix->Scale(width / image.image->GetWidth(), height / image.image->GetHeight());
        matrix->Translate(x, y);
        colorMatrix.m[4][0] = ((tintColor >> 16) & 0xff) / 255.0f;
        colorMatrix.m[4][1] = ((tintColor >> 8) & 0xff) / 255.0f;
        colorMatrix.m[4][2] = (tintColor & 0xff) / 255.0f;
        colorMatrix.m[3][3] = ((tintColor >> 24) & 0xff) / 255.0f;
        colorMatrixEffect->SetParameters(&colorMatrix);
        graphics->DrawImage(image.image, &Gdiplus::RectF(0, 0, image.image->GetWidth(), image.image->GetHeight()), matrix, colorMatrixEffect, nullptr, Gdiplus::Unit::UnitPixel);
    }

    void GdiCanvas::drawImage(const GdiImage& image, Gdiplus::RectF src, Gdiplus::RectF dst) {
        matrix->Reset();
        matrix->Translate(dst.X - src.X, dst.Y - src.Y);
        matrix->Scale(dst.Width / src.Width, dst.Height / src.Height);
        graphics->DrawImage(image.image, &src, matrix, nullptr, nullptr, Gdiplus::Unit::UnitPixel);
    }

    void GdiCanvas::drawImage(const GdiImage& image, Gdiplus::RectF src, Gdiplus::RectF dst,  int32_t tintColor) {
        matrix->Reset();
        matrix->Translate(dst.X - src.X, dst.Y - src.Y);
        matrix->Scale(dst.Width / src.Width, dst.Height / src.Height);
        colorMatrix.m[4][0] = ((tintColor >> 16) & 0xff) / 255.0f;
        colorMatrix.m[4][1] = ((tintColor >> 8) & 0xff) / 255.0f;
        colorMatrix.m[4][2] = (tintColor & 0xff) / 255.0f;
        colorMatrix.m[3][3] = ((tintColor >> 24) & 0xff) / 255.0f;
        colorMatrixEffect->SetParameters(&colorMatrix);
        graphics->DrawImage(image.image, &src, matrix, colorMatrixEffect, nullptr, Gdiplus::Unit::UnitPixel);
    }
    
    DrawingCache* GdiCanvas::endCache() {
        endPaint();
        return ghnew GdiDrawingCache(bitmap);
    }
}