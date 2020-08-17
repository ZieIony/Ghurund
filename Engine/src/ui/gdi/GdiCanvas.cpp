#include "GdiCanvas.h"

namespace Ghurund::UI {
    void GdiCanvas::drawImage(Gdiplus::Image& image, float x, float y, Gdiplus::RectF src, int32_t tintColor) {
        matrix->Reset();
        matrix->Translate(x - src.X, y - src.Y);
        colorMatrix.m[4][0] = ((tintColor >> 16) & 0xff) / 255.0f;
        colorMatrix.m[4][1] = ((tintColor >> 8) & 0xff) / 255.0f;
        colorMatrix.m[4][2] = (tintColor & 0xff) / 255.0f;
        colorMatrix.m[3][3] = ((tintColor >> 24) & 0xff) / 255.0f;
        colorMatrixEffect->SetParameters(&colorMatrix);
        graphics->DrawImage(&image, &src, matrix, colorMatrixEffect, nullptr, Gdiplus::Unit::UnitPixel);
    }
}