#pragma once

#include "GdiFont.h"
#include "ui/Canvas.h"

#include <uxtheme.h>

#pragma comment (lib, "UxTheme.lib")

namespace Ghurund {
    class GdiCanvas : public Canvas {
    private:
        PAINTSTRUCT ps = {};
        HWND hwnd = {};
        HPAINTBUFFER hbuff;
        Gdiplus::Graphics *graphics = nullptr;
        Gdiplus::Color color;
        Gdiplus::Pen* pen = nullptr;
        Gdiplus::SolidBrush* brush = nullptr;
        List<Gdiplus::GraphicsState> states;

    public:
        GdiCanvas(HWND hwnd) {
            BufferedPaintInit();
            this->hwnd = hwnd;
            pen = new Gdiplus::Pen(Gdiplus::Color());
            brush = new Gdiplus::SolidBrush(Gdiplus::Color());
        }

        ~GdiCanvas() {
            BufferedPaintUnInit();
            delete pen;
            delete brush;
        }

        void beginPaint() {
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            HDC memdc;
            hbuff = BeginBufferedPaint(hdc, &rc, BPBF_COMPATIBLEBITMAP, NULL, &memdc);
            graphics = Gdiplus::Graphics::FromHDC(memdc);
            graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
            graphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
        }

        void endPaint() {
            EndBufferedPaint(hbuff, TRUE);
            EndPaint(hwnd, &ps);
            delete graphics;
            graphics = nullptr;
        }

        void clear(unsigned int color) {
            this->color.SetValue(color);
            graphics->Clear(this->color);
        }

        void drawRect(float x, float y, float width, float height, const Paint& paint) {
            color.SetValue(paint.Color);
            pen->SetColor(color);
            graphics->DrawRectangle(pen, Gdiplus::RectF(x, y, width, height));
        }

        void fillRect(float x, float y, float width, float height, const Paint& paint) {
            color.SetValue(paint.Color);
            brush->SetColor(color);
            graphics->FillRectangle(brush, Gdiplus::RectF(x, y, width, height));
        }

        void drawLine(float x1, float y1, float x2, float y2, const Paint& paint) {
            color.SetValue(paint.Color);
            pen->SetColor(color);
            Gdiplus::GraphicsPath path;
            path.AddLine(Gdiplus::PointF(x1, y1), Gdiplus::PointF(x2, y2));
            graphics->DrawPath(pen, &path);
        }

        void drawText(const String& text, float x, float y, float width, float height, const Ghurund::Font& font, const Paint& paint);

        void translate(float x, float y) {
            graphics->TranslateTransform(x, y);
        }

        void save() {
            states.add(graphics->Save());
        }

        void restore() {
            Gdiplus::GraphicsState state = states.get(states.Size - 1);
            graphics->Restore(state);
            states.removeAtKeepOrder(states.Size - 1);
        }
    };
}